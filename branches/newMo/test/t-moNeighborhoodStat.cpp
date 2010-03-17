/*
<t-moNeighborhoodStat.cpp>
Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  ue,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.
The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.

ParadisEO WebSite : http://paradiseo.gforge.inria.fr
Contact: paradiseo-help@lists.gforge.inria.fr
*/

#include <continuator/moNeighborhoodStat.h>
#include <continuator/moMaxNeighborStat.h>
#include <continuator/moMinNeighborStat.h>
#include <continuator/moNbInfNeighborStat.h>
#include <continuator/moNbSupNeighborStat.h>
#include <continuator/moNeutralDegreeNeighborStat.h>
#include <continuator/moSecondMomentNeighborStat.h>
#include <continuator/moSizeNeighborStat.h>
#include <comparator/moNeighborComparator.h>
#include <comparator/moSolNeighborComparator.h>
#include "moTestClass.h"

#include <iostream>
#include <cstdlib>
#include <cassert>

/*
 * Tests all classes depending of moNeighborhoodStat.h
 */
int main(){

	//test de moNeighborhoodStat.h
	std::cout << "[t-moNeighborhoodStat] => START" << std::endl;

	moNeighborComparator<bitNeighbor> neighborComp;
	moSolNeighborComparator<bitNeighbor> solNeighborComp;
	evalOneMax eval(10);

	bitNeighborhood n(10);

	bitVector sol;

	sol.push_back(true);
	sol.push_back(false);
	sol.push_back(true);
	sol.push_back(true);
	sol.push_back(false);
	sol.push_back(true);
	sol.push_back(false);
	sol.push_back(true);
	sol.push_back(true);
	sol.push_back(true);

	sol.fitness(7);


	moNeighborhoodStat<bitNeighborhood> test(n, eval, neighborComp, solNeighborComp);

	test(sol);

	assert(test.getMin()==8);
	assert(test.getMax()==6);
	assert(test.getMean()==6.6);
	double sd=test.getSD();
	assert(test.getSD()>0.966 && test.getSD()<0.967);
	assert(test.getSize()==10);
	assert(test.getNbSup()==7);
	assert(test.getNbInf()==3);
	assert(test.getNbEqual()==0);

	std::cout << "[t-moNeighborhoodStat] => OK" << std::endl;

	//test of moMaxNeighborStat.h
	std::cout << "[t-moMaxNeighborStat] => START" << std::endl;
	moMaxNeighborStat<bitNeighborhood> test2(test);
	test2(sol);
	assert(test2.value()==6);
	std::cout << "[t-moMaxNeighborStat] => OK" << std::endl;

	//test of moMinNeighborStat.h
	std::cout << "[t-moMinNeighborStat] => START" << std::endl;
	moMinNeighborStat<bitNeighborhood> test3(test);
	test3(sol);
	assert(test3.value()==8);
	std::cout << "[t-moMinNeighborStat] => OK" << std::endl;

	//test of moNbInfNeighborStat.h
	std::cout << "[t-moNbInfNeighborStat] => START" << std::endl;
	moNbInfNeighborStat<bitNeighborhood> test4(test);
	test4(sol);
	assert(test4.value()==3);
	std::cout << "[t-moNbInfNeighborStat] => OK" << std::endl;

	//test of moNbSupNeighborStat.h
	std::cout << "[t-moNbSupNeighborStat] => START" << std::endl;
	moNbSupNeighborStat<bitNeighborhood> test5(test);
	test5(sol);
	assert(test5.value()==7);
	std::cout << "[t-moNbSupNeighborStat] => OK" << std::endl;

	//test of moNeutralDegreeNeighborStat.h
	std::cout << "[t-moNeutralDegreeNeighborStat] => START" << std::endl;
	moNeutralDegreeNeighborStat<bitNeighborhood> test6(test);
	test6(sol);
	assert(test6.value()==0);
	std::cout << "[t-moNeutralDegreeNeighborStat] => OK" << std::endl;

	//test of moSecondMomentNeighborStat.h
	std::cout << "[t-moSecondMomentNeighborStat] => START" << std::endl;
	moSecondMomentNeighborStat<bitNeighborhood> test7(test);
	test7(sol);
	assert(test7.value().first==6.6);
	assert(test7.value().second > 0.966 && test7.value().second < 0.967);
	std::cout << "[t-moSecondMomentNeighborStat] => OK" << std::endl;

	//test of moSizeNeighborStat.h
	std::cout << "[t-moSizeNeighborStat] => START" << std::endl;
	moSizeNeighborStat<bitNeighborhood> test8(test);
	test8(sol);
	assert(test8.value()==10);
	std::cout << "[t-moSizeNeighborStat] => OK" << std::endl;

	return EXIT_SUCCESS;
}

