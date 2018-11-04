#ifndef NWNX_RESMAN_H
#define NWNX_RESMAN_H

#include <string>
#include <unordered_map>

#include "API/CAppManager.hpp"
#include "API/CExoString.hpp"
#include "API/CNWSClient.hpp"
#include "API/CNWSDungeonMaster.hpp"
#include "API/CNWSMessage.hpp"
#include "API/CNWSPlayer.hpp"
#include "API/Constants.hpp"
#include "API/CServerExoApp.hpp"
#include "API/CVirtualMachine.hpp"
#include "API/Functions.hpp"
#include "API/Globals.hpp"
#include "Services/Config/Config.hpp"
#include "Services/Hooks/Hooks.hpp"
#include "ViewPtr.hpp"

using namespace NWNXLib;

#define MAXPATH 512

int HookFunctions();
bool RegisterDirectoryHandlers();

struct CResFileInfo {
    CResFileInfo() : size(0), mtime(0), latest_mtime(0), key(NULL) {}
    off_t size;
    time_t mtime;
    time_t latest_mtime;
    CKeyTableEntry *key;
};

typedef std::unordered_map<std::string, CResFileInfo> ResourceMap;

class CNWNXResMan : public CNWNXBase
{
    void WriteLogHeader();
    void LoadConfiguration();

public:
    CNWNXResMan();
    virtual ~CNWNXResMan();
    bool OnCreate(gline *config, const char* LogDir);
    char* OnRequest(char* gameObject, char* Request, char* Parameters);
    bool OnRelease();

    void *DemandRes(CExoResMan *pResMan, CRes* cRes, const CResRef& resRef, NwnResType resType);
    void DumpResStruct(CRes *cRes);
    bool ResourceExists(const CResRef& resRef, NwnResType resType, CKeyTableEntry **original);
    CKeyTableEntry *CreateKeyTableEntry(const CResRef& resRef, NwnResType resType);
    const char* GetSourcePath();
    bool debugCRes;
private:
    char *pScriptBuffer;
    bool warnMissing;
    HANDLE hDemandRes;
    HANDLE hResExists;
    ResourceMap resFiles;
    std::string m_sourcePath;
};

#endif // NWNX_RESMAN_H
