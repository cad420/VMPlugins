#include <VMCoreExtension/i3dblockfileplugininterface.h>
#include <VMCoreExtension/plugin.h>
#include <VMUtils/nonnull.hpp>
#include <VMUtils/concepts.hpp>
#include "VMUtils/vmnew.hpp"

namespace voxel_extract
{
namespace detail
{
struct VoxelExtractorImpl;
}

struct VoxelExtractor : ::vm::EverythingBase<I3DBlockFilePluginInterface>
{
	VoxelExtractor(::vm::IRefCnt *cnt );
	~VoxelExtractor();

public:
	void Open( const std::string &fileName ) override;
	int GetPadding() const override;
	vm::Size3 GetDataSizeWithoutPadding() const override;
	vm::Size3 Get3DPageSize() const override;
	vm::Size3 Get3DPageCount() const override;
	int Get3DPageSizeInLog() const override;
	const void *GetPage( size_t pageID ) override;
	size_t GetPageSize() const override;
	size_t GetPhysicalPageCount() const override;
	size_t GetVirtualPageCount() const override;

private:
	vm::Box<detail::VoxelExtractorImpl> _;
};


}  // namespace voxel_extract


struct VoxelExtractorFactory : vm::IPluginFactory
{
	DECLARE_PLUGIN_FACTORY( "visualman.blockdata.io" )

	::vm::IEverything *Create( const std::string &key ) override
	{
		return VM_NEW<voxel_extract::VoxelExtractor>();
	}

	std::vector<std::string> Keys() const override
	{
		return { ".comp" };
	}
};

VM_REGISTER_PLUGIN_FACTORY_DECL( VoxelExtractorFactory )

EXPORT_PLUGIN_FACTORY( VoxelExtractorFactory )
