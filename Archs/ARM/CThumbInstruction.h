#pragma once
#include "Util/CommonClasses.h"
#include "Commands/CAssemblerCommand.h"
#include "ThumbOpcodes.h"
#include "Arm.h"
#include "Core/Expression.h"
#include "ThumbOpcodes.h"

struct ThumbOpcodeVariables {
	ArmRegisterValue rd;
	ArmRegisterValue rs;
	ArmRegisterValue rn;
	ArmRegisterValue ro;
	Expression ImmediateExpression;
	int Immediate;
	int ImmediateBitLen;
	int OriginalImmediate;
	int rlist;
	char RlistStr[32];
} ;

class CThumbInstruction: public CAssemblerCommand
{
public:
	CThumbInstruction(const tThumbOpcode& sourceOpcode, ThumbOpcodeVariables& vars);

	CThumbInstruction();
//	~CThumbInstruction();
	bool Load(char* Name, char* Params);
	virtual bool Validate();
	virtual void Encode();
	virtual void writeTempData(TempData& tempData);
	size_t GetSize() { return OpcodeSize; };
private:
	void FormatInstruction(const char* encoding, char* dest);
	void WriteInstruction(unsigned short encoding);
	ThumbOpcodeVariables Vars;
	tThumbOpcode Opcode;
	bool NoCheckError;
	bool Loaded;
	size_t OpcodeSize;
	u64 RamPos;
};
