#pragma once
#include "Archs/Architecture.h"
#include "Util/CommonClasses.h"
#include "Pool.h"
#include "Core/Expression.h"
#include "Parser/Tokenizer.h"

#define ARM_SHIFT_LSL		0x00
#define ARM_SHIFT_LSR		0x01
#define ARM_SHIFT_ASR		0x02
#define ARM_SHIFT_ROR		0x03
#define ARM_SHIFT_RRX		0x04

typedef struct {
	const char* name;
	short num;
	short len;
} tArmRegister;

typedef struct {
	char Name[4];
	int Number;
} tArmRegisterInfo;

struct ArmRegisterValue
{
	std::wstring name;
	int num;
};

extern const tArmRegister ArmRegister[];

class CArmArchitecture: public CArchitecture
{
public:
	CArmArchitecture();
	~CArmArchitecture();
	void clear();

	virtual CAssemblerCommand* parseDirective(Tokenizer& tokenizer);
	virtual CAssemblerCommand* parseOpcode(Tokenizer& tokenizer);
	virtual void AssembleOpcode(const std::wstring& name, const std::wstring& args);
	virtual bool AssembleDirective(const std::wstring& name, const std::wstring& args);
	virtual void NextSection();
	virtual void Pass2();
	virtual void Revalidate();
	virtual int GetWordSize() { return 4; };
	virtual IElfRelocator* getElfRelocator();
	virtual Endianness getEndianness() { return Endianness::Little; };
	void SetThumbMode(bool b) { thumb = b; };
	bool GetThumbMode() { return thumb; };
	void SetArm9(bool b) { arm9 = b; };
	bool isArm9() { return arm9; };
	size_t NewPool() { return PoolCount++; };
	ArmPool& GetPool(size_t num) { return Pools[num]; };
	int AddToCurrentPool(int value);
	void NextPool() { CurrentPool++; };
private:
	bool thumb;
	bool arm9;
	ArmPool* Pools;
	size_t PoolCount;
	size_t CurrentPool;
};

extern CArmArchitecture Arm;
