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
	ysl::Size3 GetDataSizeWithoutPadding() const override;
	ysl::Size3 Get3DPageSize() const override;
	ysl::Size3 Get3DPageCount() const override;
	int Get3DPageSizeInLog() const override;
	const void *GetPage( size_t pageID ) override;
	size_t GetPageSize() const override;
	size_t GetPhysicalPageCount() const override;
	size_t GetVirtualPageCount() const override;

private:
	vm::Box<detail::VoxelExtractorImpl> _;
};

struct VoxelExtractorFactory : ysl::IPluginFactory
{
	DECLARE_PLUGIN_FACTORY( "visualman.blockdata.io" )

	::vm::IEverything *Create( const std::string &key ) override
	{
		return VM_NEW<VoxelExtractor>();
	}

	std::vector<std::string> Keys() const override
	{
		return {".comp"};
	}
};

}  // namespace voxel_extract

EXPORT_PLUGIN_FACTORY( voxel_extract::VoxelExtractorFactory )
