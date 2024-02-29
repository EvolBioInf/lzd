/***** complexity.h *******************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Wed Jul 15 10:55:13 2015
 **************************************************/
#ifndef COMPLEXITY
#define COMPLEXITY

#include "sequenceData.h"
#include "interface.h"
#include "factor.h"

LempelZivFact *lzComplexity(Sequence *seq);
LempelZivFact *mlComplexity(Sequence *seq);

#endif
