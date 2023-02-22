// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include "traincar.h"
#include <algorithm>

void PushBack(TrainCar*& aTraincar, TrainCar* bTraincar) {
	if (aTraincar == NULL) {
		aTraincar = bTraincar;
		return;
	}
	TrainCar* currentCar = aTraincar;
	// Set currentCar to the last car
	bool endFound = (currentCar->next == NULL);
	while (!endFound) {
		currentCar = currentCar->next;
		endFound = (currentCar->next == NULL);
	}
	// Set next car for current Car and prev car for the added car
	currentCar->next = bTraincar;
	bTraincar->prev = currentCar;
	return;
}
void DeleteAllCars(TrainCar* aTraincar) {
	if (aTraincar == NULL) {
		return;
	}
	TrainCar* currentCar = aTraincar;
	// If there is only 1 car in the sequence
	if (currentCar->next == NULL) {
		delete currentCar;
		return;
	}
	TrainCar* prevCar;
	// Set currentCar to the last car in the list
	while (currentCar->next != NULL) {
		currentCar = currentCar->next;
	}
	// Delete last element and shift 1 spot down
	prevCar = currentCar->prev;
	while (prevCar->prev != NULL) {
		delete currentCar;
		currentCar = prevCar;
		prevCar = currentCar->prev;
	}
	// Delete the last two elements
	delete currentCar;
	delete prevCar;
	return;
}
void TotalWeightAndCountCars(TrainCar* train, int& total_weight,
		int& num_engines, int& num_freight_cars, int& num_passenger_cars,
		int& num_dining_cars, int& num_sleeping_cars) {
	// Set all numbers to 0
	total_weight = 0;
	num_engines = 0;
	num_freight_cars = 0;
	num_passenger_cars = 0;
	num_dining_cars = 0;
	num_sleeping_cars = 0;
	if (train == NULL) {
		return;
	}
	TrainCar* currentCar = train;
	while (currentCar != NULL) {
		AddNumbers(currentCar, total_weight, 
				num_engines, num_freight_cars, num_passenger_cars, 
				num_dining_cars, num_sleeping_cars);
		currentCar = currentCar->next;
	}
	return;
}
void AddNumbers(TrainCar* currentCar, int& total_weight,
		int& num_engines, int& num_freight_cars, int& num_passenger_cars,
		int& num_dining_cars, int& num_sleeping_cars) {
	if (currentCar->isEngine()) {
		num_engines += 1;
	} else if (currentCar->isFreightCar()) {
		num_freight_cars += 1;
	} else if (currentCar->isPassengerCar()) {
		num_passenger_cars += 1;
	} else if (currentCar->isDiningCar()) {
		num_dining_cars += 1;
	} else if (currentCar->isSleepingCar()) {
		num_sleeping_cars += 1;
	}
	total_weight += currentCar->getWeight();
	return;
}
float CalculateSpeed(TrainCar* aTrainCar) {
	if (aTrainCar == NULL) {
		return 0;
	}
	int total_weight, num_engines, num_freight_cars, 
		num_passenger_cars, num_dining_cars, num_sleeping_cars;
	TotalWeightAndCountCars(aTrainCar, total_weight, num_engines, 
			num_freight_cars, num_passenger_cars, 
			num_dining_cars, num_sleeping_cars);
	return (3000*(float)num_engines*550*3600)/((20/0.01)*0.02*5280*(float)total_weight);
}
float CalculatePossibleSpeed(TrainCar* aTrainCar, TrainCar* bTrainCar) {
	if (aTrainCar == NULL) {
		return 0;
	}
	int total_weight, num_engines, num_freight_cars, 
		num_passenger_cars, num_dining_cars, num_sleeping_cars;
	TotalWeightAndCountCars(aTrainCar, total_weight, num_engines, 
			num_freight_cars, num_passenger_cars, 
			num_dining_cars, num_sleeping_cars);
	return (3000*(float)num_engines*550*3600)/((20/0.01)*0.02*5280*(float)(total_weight + bTrainCar->getWeight()));
}
float AverageDistanceToDiningCar(TrainCar* aTrainCar) {
	unsigned int numCargoCars = 0;
	float totalDistance = 0;
	if (aTrainCar == NULL) {
		return -1;
	}
	while (aTrainCar != NULL) {
		if (aTrainCar->isPassengerCar()) {
			float currentDistance = CurrentDistanceToDiningCar(aTrainCar);
			if (currentDistance == -1) {
				return -1;
			}
			numCargoCars += 1;
			totalDistance += currentDistance;
		}
		aTrainCar = aTrainCar->next;
	}
	return totalDistance/numCargoCars;
}
float CurrentDistanceToDiningCar(TrainCar* aTrainCar) {
	float goingLeft = 0;
	float goingRight = 0;
	TrainCar* currentCar = aTrainCar;
	while (true) {
		currentCar = currentCar->prev;
		if (currentCar == NULL || (*currentCar).isEngine() ||
				(*currentCar).isFreightCar()) {
			goingLeft = -1;
			break;
		}
		goingLeft += 1;
		if (currentCar->isDiningCar()) {
			break;
		}
	}
	currentCar = aTrainCar;
	while (true) {
		currentCar = currentCar->next;
		if (currentCar == NULL || (*currentCar).isEngine() ||
				(*currentCar).isFreightCar()) {
			goingRight = -1;
			break;
		}
		goingRight += 1;
		if (currentCar->isDiningCar()) {
			break;
		}
	}
	if (goingLeft == -1 && goingRight == -1) {
		return -1;
	} else if (goingLeft == -1) {
		return goingRight;
	} else if (goingRight == -1) {
		return goingLeft;
	} else {
		return std::min(goingLeft, goingRight);
	}
}
int ClosestEngineToSleeperCar(TrainCar* aTraincar) {
	int minDistance = -1;
	if (aTraincar == NULL) {
		return -1;
	}
	while (aTraincar != NULL) {
		if (aTraincar->isSleepingCar()) {
			int currentDistance = CurrentDistanceToEngineCar(aTraincar);
			if ((currentDistance != -1 && currentDistance < minDistance) ||
					(currentDistance != -1 && minDistance == -1)) {
				minDistance = currentDistance;
			}
		}
		aTraincar = aTraincar->next;
	}
	return minDistance;
}
int CurrentDistanceToEngineCar(TrainCar* aTraincar) {
	int goingLeft = 0;
	int goingRight = 0;
	TrainCar* currentCar = aTraincar;
	while (true) {
		currentCar = currentCar->prev;
		if (currentCar == NULL) {
			goingLeft = -1;
			break;
		}
		goingLeft += 1;
		if (currentCar->isEngine()) {
			break;
		}
	}
	currentCar = aTraincar;
	while (true) {
		currentCar = currentCar->next;
		if (currentCar == NULL) {
			goingRight = -1;
			break;
		}
		goingRight += 1;
		if (currentCar->isEngine()) {
			break;
		}
	}
	if (goingLeft == -1 && goingRight == -1) {
		return -1;
	} else if (goingLeft == -1) {
		return goingRight;
	} else if (goingRight == -1) {
		return goingLeft;
	} else {
		return std::min(goingLeft, goingRight);
	}
	return -1;
}
std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines, 
		TrainCar*& all_freight, float min_speed, int max_cars_per_train) {
	std::vector<TrainCar*> allTrains;
	allTrains.push_back(NULL);
	int currentTrain = 0;
	int currentTrainLength = 0;
	while (true) {
		float currentSpeed = CalculateSpeed(allTrains[currentTrain]);
		float possibleSpeed = 0;
		if (all_freight != NULL) {
			possibleSpeed = CalculatePossibleSpeed(allTrains[currentTrain], all_freight);
		}
		// Conditions to go to next train are
		// If youve reached the max number of train cars
		// or you have 1 less than the max traincars and adding another 
		// would put you under the minimum speed
		if (((currentTrainLength == max_cars_per_train) || 
					(currentTrainLength == max_cars_per_train - 1 
					 && possibleSpeed <= min_speed && !(currentSpeed < min_speed))) 
				&& (all_freight != NULL && all_engines != NULL)) {
			allTrains.push_back(NULL);
			currentTrain += 1;
			currentTrainLength = 0;
			continue;
		}
		if ((currentSpeed > min_speed && all_freight != NULL && currentTrainLength != max_cars_per_train)
				&& (possibleSpeed >= min_speed || (all_engines != NULL && currentTrainLength <= max_cars_per_train - 2))) {
			TrainCar* nextFreightCar = all_freight;
			DisconnectFromTrain(nextFreightCar, all_freight);
			PushBack(allTrains[currentTrain], nextFreightCar);
			currentTrainLength += 1;
		} else if (currentSpeed <= min_speed && all_engines != NULL && currentTrainLength != max_cars_per_train) {
			TrainCar* nextEngine = all_engines;
			DisconnectFromTrain(nextEngine, all_engines);
			AddEngine(allTrains[currentTrain], nextEngine);
			currentTrainLength += 1;
		} else {
			break;
		}
	}
	return allTrains;
}
// Adds engine to the end of the engine chain for a certain train
void AddEngine(TrainCar*& aTrainCar, TrainCar*& aEngineCar) {
	// First check if there are any engines
	if (aEngineCar == NULL) {
		std::cout << "Error... Engine trying to be added is NULL" << std::endl;
		return;
	} else if (!(aEngineCar->isEngine())) {
		std::cout << "Error... Engine added is not an engine" << std::endl;
		return;
	}
	// Next, get a reference to the position you want to enter the engine into
	TrainCar* currentCar = aTrainCar;
	// If there are cars in the list
	if (currentCar != NULL) {
		while (currentCar->isEngine()) {
			// If this car isn't the last in the list
			if (currentCar->next != NULL) {
				currentCar = currentCar->next;
				// If the train is all engines
			} else {
				PushBack(aTrainCar, aEngineCar);
				return;
			}
		}
		// If there are no cars in the list
	} else {
		PushBack(aTrainCar, aEngineCar);
		return;
	}
	// currentCar is one after the insert
	// Get a reference to one car before the insert
	TrainCar* prevCar = currentCar->prev;
	// Insert engine into the train
	if (prevCar != NULL) {
		prevCar->next = aEngineCar;
		aEngineCar->prev = prevCar;
	}
	currentCar->prev = aEngineCar;
	aEngineCar->next = currentCar;
	// Set aTrainCar to the first car in the list
	aTrainCar = aEngineCar;
	while (true) {
		if (aTrainCar->prev == NULL) {
			break;
		}
		aTrainCar = aTrainCar->prev;
	}
	return;
}
void DisconnectFromTrain(TrainCar* aTrainCar, TrainCar*& startOfTrain) {
	// If removing the first TrainCar, shift over the pointer to the start of the train
	// If the disconnected index was the only one in, startOfTrain just becomes NULL
	if (aTrainCar == startOfTrain) {
		startOfTrain = startOfTrain->next;
	}
	// Get references to the left and right
	TrainCar* left = aTrainCar->prev;
	TrainCar* right = aTrainCar->next;
	// If it isnt at the start or end of the train
	if (left != NULL && right != NULL) {
		left->next = right;
		right->prev = left;
		// If index was at the end of the train
	} else if (left != NULL) {
		left->next = NULL;
		// If index was at the start of the train
	} else if (right != NULL) {
		right->prev = NULL;
	}
	// Remove prev and next from aTrainCar
	aTrainCar->prev = NULL;
	aTrainCar->next = NULL;
	return;
}
void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3) {
	train2 = NULL;
	train3 = NULL;
	float originalSpeed = CalculateSpeed(train1);
	int total_weight, num_engines, num_freight_cars, 
		num_passenger_cars, num_dining_cars, num_sleeping_cars;
	TotalWeightAndCountCars(train1, total_weight, num_engines, 
			num_freight_cars, num_passenger_cars, 
			num_dining_cars, num_sleeping_cars);
	int originalTrainCars = num_passenger_cars + num_dining_cars + num_sleeping_cars;
	int smallerTrainEngines = (int)(num_engines/2);
	int largerTrainEngines = num_engines - smallerTrainEngines;
	int smallerTrainCars = std::round((562.5*(float)smallerTrainEngines/originalSpeed) - (3*smallerTrainEngines));
	int largerTrainCars = originalTrainCars - smallerTrainCars;
	TrainCar* startOfTrain = train1;
	TrainCar* endOfTrain = train1;
	// Get a pointer to the last traincar
	while(endOfTrain->next != NULL) {
		endOfTrain = endOfTrain->next;
	}
	while(true) {
		int tempEngines, tempCars;
		if (startOfTrain != NULL) {
			CountForward(startOfTrain, smallerTrainEngines + smallerTrainCars, tempEngines, tempCars);
			if (tempEngines == smallerTrainEngines && tempCars == smallerTrainCars) {
				// Place cars into lists
				PlaceForward(train1, startOfTrain, smallerTrainEngines + smallerTrainCars, train2, train3);
				break;
			}
			CountForward(startOfTrain, largerTrainEngines + largerTrainCars, tempEngines, tempCars);
			if (tempEngines == largerTrainEngines && tempCars == largerTrainCars) {
				PlaceForward(train1, startOfTrain, largerTrainEngines + largerTrainCars, train2, train3);
				// Place cars into lists
				break;
			}
			startOfTrain = startOfTrain->next;
		} else if (endOfTrain != NULL) {
			CountBackward(startOfTrain, smallerTrainEngines + smallerTrainCars, tempEngines, tempCars);
			if (tempEngines == smallerTrainEngines && tempCars == smallerTrainCars) {
				PlaceBackward(train1, startOfTrain, smallerTrainEngines + smallerTrainCars, train2, train3);
				// Place cars into lists
				break;
			}
			CountBackward(startOfTrain, largerTrainEngines + largerTrainCars, tempEngines, tempCars);
			if (tempEngines == largerTrainEngines && tempCars == largerTrainCars) {
				PlaceBackward(train1, startOfTrain, largerTrainEngines + largerTrainCars, train2, train3);
				// Place cars into lists
				break;
			}
			endOfTrain = endOfTrain->prev;
		}
		if (startOfTrain == NULL || endOfTrain == NULL) {
			break;
		}
	}
	return;
}
void CountForward(TrainCar* train, int num, int& numEngines, int& numCars) {
	int currentCount = 0;
	numEngines = 0;
	numCars = 0;
	if (train == NULL) {
		return;
	}
	while(currentCount < num) {
		if (train->isEngine()) {
			numEngines++;
		} else {
			numCars++;
		}
		if (train->next != NULL) {
			train = train->next;
		} else {
			break;
		}
		currentCount++;
	}
	return;
}
void CountBackward(TrainCar* train, int num, int& numEngines, int& numCars) {
	int currentCount = 0;
	numEngines = 0;
	numCars = 0;
	if (train == NULL) {
		return;
	}
	while(currentCount < num) {
		if (train->isEngine()) {
			numEngines++;
		} else {
			numCars++;
		}
		if (train->prev != NULL) {
			train = train->prev;
		} else {
			break;
		}
		currentCount++;
	}
	return;
}
void PlaceForward(TrainCar*& startOfTrain, TrainCar* breakStart, int num, TrainCar*& train1, TrainCar*& train2) {
	for (int i=0; i<num; i++) {
		TrainCar* tempTrain = breakStart;
		breakStart = breakStart->next;
		DisconnectFromTrain(tempTrain, startOfTrain);
		PushBack(train1, tempTrain);
	}
	train2 = startOfTrain;
	startOfTrain = NULL;
}
void PlaceBackward(TrainCar*& startOfTrain, TrainCar* breakStart, int num, TrainCar*& train1, TrainCar*& train2) {
	for (int i=0; i<num; i++) {
		TrainCar* tempTrain = breakStart;
		breakStart = breakStart->prev;
		DisconnectFromTrain(tempTrain, startOfTrain);
		PushBack(train1, tempTrain);
	}
	train2 = startOfTrain;
	startOfTrain = NULL;
}
// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//
