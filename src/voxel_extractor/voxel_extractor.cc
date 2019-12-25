#include "voxel_extractor.hpp"
#include <VMat/numeric.h>
#include <VMFoundation/pluginloader.h>
#include <vocomp/refine/extractor.hpp>
#include <VMCoreExtension/ifilemappingplugininterface.h>
#include <vocomp/refine/pipe_factory.hpp>
#include <VMUtils/ref.hpp>

using namespace vol;
using namespace std;
using namespace vm;

namespace voxel_extract
{
namespace detail
{
struct VoxelExtractorImpl : vm::NoCopy, vm::NoMove
{
	void Open( const std::string &fileName )
	{
#ifdef _WIN32
		file_mapping = vm::PluginLoader::GetPluginLoader()->CreatePlugin<IMappingFile>( "windows" );
#else
		file_mapping = PluginLoader::GetPluginLoader()->CreatePlugin<IMappingFile>( "linux" );
#endif

		if ( file_mapping == nullptr ) {
			throw std::runtime_error( "failed to load file mapping plugin" );
		}

		std::ifstream file_size( fileName );
		if ( file_size.is_open() == false ) {
			throw std::runtime_error( "can not file file" );
		}

		file_size.seekg( 0, std::ios::end );
		const size_t file_bytes = file_size.tellg();
		file_size.close();

		if ( file_mapping->Open( fileName, file_bytes, FileAccess::Read, MapAccess::ReadOnly ) == false ) {
			vm::println( "Failed to open file {}", fileName );
		}

		auto in = (char *)file_mapping->FileMemPointer( 0, file_bytes );
		vm::println( "{}", make_pair( (void *)in, file_bytes ) );
		reader.reset( new SliceReader( in, file_bytes ) );
		_.reset( new vol::refine::Extractor( *reader ) );

		pipe.reset( PipeFactory::create( fileName ) );
		video_decompressor = dynamic_cast<vol::video::Decompressor *>( pipe.get() );

		buf.resize( GetPageSize() * 2 );
		w.reset( new SliceWriter( buf.data(), GetPageSize() ) );
	}
	int GetPadding()
	{
		return _->padding();
	}
	vm::Size3 GetDataSizeWithoutPadding()
	{
		return vm::Size3{
			_->raw().x,
			_->raw().y,
			_->raw().z,
		};
	}
	vm::Size3 Get3DPageSize()
	{
		return vm::Size3{
			_->block_size(),
			_->block_size(),
			_->block_size(),
		};
	}
	vm::Size3 Get3DPageCount()
	{
		return vm::Size3{
			_->dim().x,
			_->dim().y,
			_->dim().z,
		};
	}
	int Get3DPageSizeInLog()
	{
		return _->log_block_size();
	}
	const void *GetPage( size_t pageID )
	{
		auto xyz = vm::Dim( pageID, vm::Size2( _->dim().x, _->dim().y ) );
		auto r = _->extract( index::Idx{}
							   .set_x( xyz.x )
							   .set_y( xyz.y )
							   .set_z( xyz.z ) );
		w->seek( 0 );
		if ( video_decompressor ) {
			cufx::MemoryView1D<unsigned char> view( buf.data(), buf.size() );
			video_decompressor->decompress( r, view );
		} else {
			pipe->transfer( r, *w );
		}
		return buf.data();
	}
	size_t GetPageSize()
	{
		return _->block_size() * _->block_size() * _->block_size();
	}
	size_t GetPhysicalPageCount()
	{
		return _->dim().x * _->dim().y * _->dim().z;
	}
	size_t GetVirtualPageCount()
	{
		return _->dim().x * _->dim().y * _->dim().z;
	}

	::vm::Ref<IMappingFile> file_mapping;
	unique_ptr<SliceReader> reader;
	unique_ptr<refine::Extractor> _;
	unique_ptr<Pipe> pipe;
	video::Decompressor *video_decompressor = nullptr;
	vector<char> buf;
	unique_ptr<SliceWriter> w;
};

}  // namespace detail

VoxelExtractor::VoxelExtractor( ::vm::IRefCnt *cnt ) :
  ::vm::EverythingBase<I3DBlockFilePluginInterface>( cnt ),
  _( new detail::VoxelExtractorImpl() )
{
}

VoxelExtractor::~VoxelExtractor()
{
}

void VoxelExtractor::Open( const std::string &fileName )
{
	return _->Open( fileName );
}
int VoxelExtractor::GetPadding() const
{
	return _->GetPadding();
}
vm::Size3 VoxelExtractor::GetDataSizeWithoutPadding() const
{
	return _->GetDataSizeWithoutPadding();
}
vm::Size3 VoxelExtractor::Get3DPageSize() const
{
	return _->Get3DPageSize();
}
vm::Size3 VoxelExtractor::Get3DPageCount() const
{
	return _->Get3DPageCount();
}
int VoxelExtractor::Get3DPageSizeInLog() const
{
	return _->Get3DPageSizeInLog();
}
const void *VoxelExtractor::GetPage( size_t pageID )
{
	return _->GetPage( pageID );
}
size_t VoxelExtractor::GetPageSize() const
{
	return _->GetPageSize();
}
size_t VoxelExtractor::GetPhysicalPageCount() const
{
	return _->GetPhysicalPageCount();
}
size_t VoxelExtractor::GetVirtualPageCount() const
{
	return _->GetVirtualPageCount();
}

}  // namespace voxel_extract

VM_REGISTER_PLUGIN_FACTORY_IMPL( VoxelExtractorFactory )

EXPORT_PLUGIN_FACTORY_IMPLEMENT( VoxelExtractorFactory )
