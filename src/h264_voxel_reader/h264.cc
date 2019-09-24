#include <pagefileinterface.h>
#include <memory>
#include <vector>
#include <string>

namespace ysl
{
struct H264VoxelReader : I3DBlockFilePluginInterface
{
	DECLARE_RTTI

public:
	void Open( const std::string &filename ) override;
	const void *GetPage( std::size_t page_id ) override;
	std::size_t GetPageSize() const override;
	std::size_t GetPhysicalPageCount() const override;
	std::size_t GetVirtualPageCount() const override;

	int GetPadding() const override;
	Size3 GetDataSizeWithoutPadding() const override;
	Size3 Get3DPageSize() const override;
	int Get3DPageSizeInLog() const override;
	Size3 Get3DPageCount() const override;
};

struct H264VoxelReaderFactory : IPluginFactory
{
	DECLARE_PLUGIN_FACTORY( "visualman.blockdata.io" )
public:
	std::vector<std::string> Keys() const override;
	std::unique_ptr<Object> Create(const std::string &key) override;
};

}  // namespace ysl

EXPORT_PLUGIN_FACTORY( ysl::H264VoxelReaderFactory )
