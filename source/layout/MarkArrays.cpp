/*
 * @(#)MarkArrays.cpp	1.5 00/03/15
 *
 * (C) Copyright IBM Corp. 1998, 1999, 2000 - All Rights Reserved
 *
 */

#include "LETypes.h"
#include "LEFontInstance.h"
#include "OpenTypeTables.h"
#include "AnchorTables.h"
#include "MarkArrays.h"
#include "LESwaps.h"

le_int32 MarkArray::getMarkClass(LEGlyphID glyphID, le_int32 coverageIndex, LEFontInstance *fontInstance,
                              LEPoint &anchor)
{
    le_int32 markClass = -1;

    if (coverageIndex >= 0) {
        le_uint16 mCount = SWAPW(markCount);

        if (coverageIndex < mCount) {
            MarkRecord *markRecord = &markRecordArray[coverageIndex];
            Offset anchorTableOffset = SWAPW(markRecord->markAnchorTableOffset);
            AnchorTable *anchorTable = (AnchorTable *) ((char *) this + anchorTableOffset);

            anchorTable->getAnchor(glyphID, fontInstance, anchor);
            markClass = SWAPW(markRecord->markClass);
        }

        // XXXX If we get here, the table is mal-formed
    }

    return markClass;
}
