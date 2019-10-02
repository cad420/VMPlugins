#ifndef _LZ4FILEREADER_H_
#define _LZ4FILEREADER_H_

#include <VMCoreExtension/ifilemappingplugininterface.h>
#include <VMCoreExtension/i3dblockfileplugininterface.h>
#include <VMCoreExtension/plugin.h>
#include <VMCoreExtension/plugindef.h>

#include <VMUtils/ref.hpp>
#include <VMat/geometry.h>
#include <fstream>
#include <vector>
#include "fileheader.h"

namespace lz4filereader
{
	using namespace vm;
	using namespace ysl;
	class LZ4FileReader :public ::vm::EverythingBase<I3DBlockFilePluginInterface>
	{
	public:
		LZ4FileReader(::vm::IRefCnt * cnt): ::vm::EverythingBase<I3DBlockFilePluginInterface>(cnt){}
		void Open(const std::string& fileName) override;
		int GetPadding() const override;
		Size3 GetDataSizeWithoutPadding() const override;
		Size3 Get3DPageSize() const override;
		Size3 Get3DPageCount() const override;
		int Get3DPageSizeInLog() const override;
		const void* GetPage(size_t pageID) override;
		size_t GetPageSize() const override;
		size_t GetPhysicalPageCount() const override;
		size_t GetVirtualPageCount() const override;
		~LZ4FileReader();
	private:
		//std::ifstream inFile;
		//std::shared_ptr<IFileMapping> fileMapping;
		::vm::Ref<IFileMapping> fileMapping;

		char* dataPtr = nullptr;
		LVDHeader header;
		std::vector<uint32_t>* blockBytes = nullptr;
		std::vector<uint64_t>* blockOffset = nullptr;
		char* blockBuf;
		char* compressedBuf;
		Size3 blockSize;
		Size3 bSize, oSize, vSize;
		size_t blockSizeBytes;
	};

	class LZ4FileReaderFactory :public IPluginFactory
	{
	public:
		DECLARE_PLUGIN_FACTORY("visualman.blockdata.io")
		::vm::IEverything * Create(const std::string& key) override;
		std::vector<std::string> Keys() const override;
	};

}

EXPORT_PLUGIN_FACTORY(lz4filereader::LZ4FileReaderFactory)
#endif