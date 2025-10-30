#ifndef ZYCHEATS_SGUYS_FUNCTIONS_H
#define ZYCHEATS_SGUYS_FUNCTIONS_H

// here you can define variables for the patches
bool addCurrency, freeItems, everythingUnlocked, showAllItems, addSkins;

monoString *CreateIl2cppString(const char *str) {
    monoString *(*String_CreateString)(void *instance, const char *str) = (monoString*(*)(void*, const char*)) (g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE("0x2596B20")));
    return String_CreateString(NULL, str);
}

void (*PurchaseRealMoney) (void* instance, monoString* itemId, monoString* receipt, void* callback);

void Pointers() {
    PurchaseRealMoney = (void(*)(void*, monoString*, monoString*, void*)) (g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE("0xE7AADC")));
}

void Patches() {
    PATCH_SWITCH("0x18383A0", "40B29AD2A0C9A0F2E019DEF20090E8F2C0035FD6", freeItems);
    PATCH_SWITCH("0x1838E00", "40B29AD2A0C9A0F2E019DEF20090E8F2C0035FD6", freeItems); 
    PATCH_SWITCH("0x1839878", "40B29AD2A0C9A0F2E019DEF20090E8F2C0035FD6", freeItems); 


 
}

// declare your hooks here
void (*old_Backend)(void *instance);
void Backend(void *instance) {
    if (instance != NULL) {
        if (addCurrency) {
            LOGW("Calling Purchase");
            PurchaseRealMoney(instance, CreateIl2cppString("special_offer1"), CreateIl2cppString("dev"), NULL);
            addCurrency = false;
        }
        if (addSkins) {
            LOGW("Calling Skins");
            addSkins = false;
        }
    }
    return old_Backend(instance);
}

void* (*old_ProductDefinition)(void *instance, monoString* id, monoString* storeSpecificId, int type, bool enabled, void* payouts);
void* ProductDefinition(void *instance, monoString* id, monoString* storeSpecificId, int type, bool enabled, void* payouts) {
    if (instance != NULL) {
        LOGW("Called ProductDefinition! Here are the parameters:");
        LOGW("id: %s", id->getChars());
        LOGW("storeSpecificId: %s", storeSpecificId->getChars());
        LOGW("type: %i", type);
    }
    return old_ProductDefinition(instance, id, storeSpecificId, type, enabled, payouts);
}

void Hooks() {
    HOOK("0xE7BC74", Backend, old_Backend);
    HOOK("0x29DA08C", ProductDefinition, old_ProductDefinition);
}

#endif //ZYCHEATS_SGUYS_FUNCTIONS_H
