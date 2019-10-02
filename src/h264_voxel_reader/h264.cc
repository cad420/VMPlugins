#include <VMCoreExtension/i3dblockfileplugininterface.h>
#include <memory>
#include <vector>
#include <string>
#include <VMat/geometry.h>
#include <VMCoreExtension/plugin.h>
#include <VMCoreExtension/plugindef.h>

struct H264VoxelReader : I3DBlockFilePluginInterface
{

public:
	void Open( const std::string &filename ) override;
	const void *GetPage( std::size_t page_id ) override;
	std::size_t GetPageSize() const override;
	std::size_t GetPhysicalPageCount() const override;
	std::size_t GetVirtualPageCount() const override;

	int GetPadding() const override;
	ysl::Size3 GetDataSizeWithoutPadding() const override;
	ysl::Size3 Get3DPageSize() const override;
	int Get3DPageSizeInLog() const override;
	ysl::Size3 Get3DPageCount() const override;
};

struct H264VoxelReaderFactory : ysl::IPluginFactory
{
public:
	std::vector<std::string> Keys() const override;
	::vm::IEverything * Create(const std::string &key) override;
};


EXPORT_PLUGIN_FACTORY(H264VoxelReaderFactory)
