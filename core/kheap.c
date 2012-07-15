/* kheap.c --> 内核堆分配函数的实现 */
/* Copyright (c) 1998 著作权由Chapaev所有。著作权人保留一切权利。
 * 
 * 这份授权条款，在使用者符合以下三条件的情形下，授予使用者使用及再散播本
 * 软件包装原始码及二进位可执行形式的权利，无论此包装是否经改作皆然：
 * 
 * * 对于本软件源代码的再散播，必须保留上述的版权宣告、此三条件表列，以
 *   及下述的免责声明。
 * * 对于本套件二进位可执行形式的再散播，必须连带以文件以及／或者其他附
 *   于散播包装中的媒介方式，重制上述之版权宣告、此三条件表列，以及下述
 *   的免责声明。
 * * 未获事前取得书面许可，不得使用本软件贡献者之名称，
 *   来为本软件之衍生物做任何表示支持、认可或推广、促销之行为。
 * 
 * 免责声明：本软件是由本软件之贡献者以现状（"as is"）提供，
 * 本软件包装不负任何明示或默示之担保责任，包括但不限于就适售性以及特定目
 * 的的适用性为默示性担保。加州大学董事会及本软件之贡献者，无论任何条件、
 * 无论成因或任何责任主义、无论此责任为因合约关系、无过失责任主义或因非违
 * 约之侵权（包括过失或其他原因等）而起，对于任何因使用本软件包装所产生的
 * 任何直接性、间接性、偶发性、特殊性、惩罚性或任何结果的损害（包括但不限
 * 于替代商品或劳务之购用、使用损失、资料损失、利益损失、业务中断等等），
 * 不负任何责任，即在该种使用已获事前告知可能会造成此类损害的情形下亦然。*/

#include <kheap.h>
//#include <heaplist.h>
#include <kcommon.h>
#include <kstdlib/kio.h>
extern u32i end;
u32i PlacementAddress = (u32i) &end;

//extern HeapListEntry* FreeList;

/*void
KHeapInit()
{
	HeapListInit();
	BlockHeader* Head = FreeList[1].Address;
	BlockFooter* Foot = FreeList[1].Address + FreeList[1].Size - sizeof(BlockFooter);
	Head->Magic = 0xC0FFEE;
	Heap->InUse = false;
	Head->Size = 4096000 - sizeof(BlockHeader) - sizeof(BlockFooter);
	Foot->Magic = 0xCOFFEE;
	Foot->Head = Head;
}
*/
u32i KmallocIntenal(u32i Size,s32i Align,u32i* Physical)
{
	/*u32i TempAddress = PlacementAddress;
	u32i AllocSize = Size;
	if ( Align == 1 && (TempAddress & 0xFFFFF000)) {
		TempAddress &= 0xFFFFF000;
		TempAddress += 0x1000;
		AllocSize += */
	if ( Align == 1 && (PlacementAddress & 0xFFFFF000)) {
		PlacementAddress &= 0xFFFFF000;
		PlacementAddress += 0x1000;
	}
	if ( Physical ) {
		*Physical = PlacementAddress;
	}
	u32i tmp = PlacementAddress;
	PlacementAddress += Size;
	return tmp;
}

u32i KmallocAligned(u32i Size)
{
	return KmallocIntenal(Size,1,0);
}

u32i KmallocPhysical(u32i Size,u32i* Physical)
{
	return KmallocIntenal(Size,0,Physical);
}

u32i KmallocAlignedPhysical(u32i Size ,u32i* Physical)
{
	return KmallocIntenal(Size,1,Physical);
}

u32i Kmalloc(u32i Size)
{
	return KmallocIntenal(Size,0,0);
}

/*void Free(u32i Address,u32i Size)
{
	HeapListEntry* ToDelete = FindHeapListEntry(Alloced,Address);
	DeleteHeapListEntry(ToDelete)
	if (Address == PlacementAddress - Size){
		PlacementAddress -= Size;
	}
	else{
		HeapListEntry* ToInsert = AllocMemory(sizeof(ToInsert));
		ToInsert->IsHead = false;
		InsertHeapListEntry(Free,ToInsert);
	}
}

void KFree(void* Pointer)
{
	HeapListEntry* Temp = FindHeapListEntry(Alloced,Address);
	if (Temp == NULL) return;
	return Free(Temp->MenRecord.Address,Temp->MenRecord.Size);
}
*/
