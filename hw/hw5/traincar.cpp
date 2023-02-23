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
// Pushes a traincar to the back of the train
void PushBack(TrainCar*& aTraincar, TrainCar* bTraincar) {
	// If the train is empty, just set the train equal to the new car
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
// Pushes new car to the front of the train
void PushFront(TrainCar*& aTraincar, TrainCar* bTraincar) {
	// If the train is empty, just set the train equal to the new car
	if (aTraincar == NULL) {
		aTraincar = bTraincar;
		return;
	}
	// Attaches the new car to the start of the train
	aTraincar->prev = bTraincar;
	bTraincar->next = aTraincar;
	// Change the start of the train pointer
	aTraincar = bTraincar;
	return;
}
// Deletes all cars in the train
void DeleteAllCars(TrainCar* aTraincar) {
	// Do nothing if the train is null
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
// add up the weight, and number of each type of car for a train
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
	// Exit out if the train is empty
	if (train == NULL) {
		return;
	}
	// Loop through each train car
	TrainCar* currentCar = train;
	while (currentCar != NULL) {
		// Add the correct weight and type of car to the numbers
		AddNumbers(currentCar, total_weight, 
				num_engines, num_freight_cars, num_passenger_cars, 
				num_dining_cars, num_sleeping_cars);
		currentCar = currentCar->next;
	}
	// Exit out of the function
	return;
}
// Add the weight and correct type of car for TotalWeightAndCountCars
void AddNumbers(TrainCar* currentCar, int& total_weight,
		int& num_engines, int& num_freight_cars, int& num_passenger_cars,
		int& num_dining_cars, int& num_sleeping_cars) {
	// Check for car type
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
	// Add the weight
	total_weight += currentCar->getWeight();
	// Exit out of the function
	return;
}
// calculate speed for a train
float CalculateSpeed(TrainCar* aTrainCar) {
	// Speed is zero if the train is empty
	if (aTrainCar == NULL) {
		return 0;
	}
	// Get the total weight and number of engines
	int total_weight, num_engines, num_freight_cars, 
		num_passenger_cars, num_dining_cars, num_sleeping_cars;
	TotalWeightAndCountCars(aTrainCar, total_weight, num_engines, 
			num_freight_cars, num_passenger_cars, 
			num_dining_cars, num_sleeping_cars);
	// Return speed given the speed formula for a train at a 2% incline
	return (3000*(float)num_engines*550*3600)/
		((20/0.01)*0.02*5280*(float)total_weight);
}
// calculate speed for a train if the train has a new car added to it
float CalculatePossibleSpeed(TrainCar* aTrainCar, TrainCar* bTrainCar) {
	// If the train is empty, speed is 0
	if (aTrainCar == NULL) {
		return 0;
	}
	// Total up the number of cars of each type and weight
	int total_weight, num_engines, num_freight_cars, 
		num_passenger_cars, num_dining_cars, num_sleeping_cars;
	TotalWeightAndCountCars(aTrainCar, total_weight, num_engines, 
			num_freight_cars, num_passenger_cars, 
			num_dining_cars, num_sleeping_cars);
	// Return modified speed formula with the new car added to it
	return (3000*(float)num_engines*550*3600)/
		((20/0.01)*0.02*5280*(float)(total_weight + bTrainCar->getWeight()));
}
// Find the average distance to a dining car for each passenger car
float AverageDistanceToDiningCar(TrainCar* aTrainCar) {
	unsigned int numCargoCars = 0;
	float totalDistance = 0;
	// If te train is empty, return -1
	if (aTrainCar == NULL) {
		return -1;
	}
	// Loop through the train
	while (aTrainCar != NULL) {
		// If the car is a passenger car
		if (aTrainCar->isPassengerCar()) {
			// Get the distance to the passenger cars
			float currentDistance = CurrentDistanceToDiningCar(aTrainCar);
			if (currentDistance == -1) {
				return -1;
			}
			numCargoCars += 1;
			totalDistance += currentDistance;
		}
		aTrainCar = aTrainCar->next;
	}
	// Average distances
	return totalDistance/numCargoCars;
}
// Helper function for AverageDistanceToDiningCar
float CurrentDistanceToDiningCar(TrainCar* aTrainCar) {
	float goingLeft = 0;
	float goingRight = 0;
	TrainCar* currentCar = aTrainCar;
	// Find distance to a dining car when moving to the left
	while (true) {
		currentCar = currentCar->prev;
		// If it hit a engine or freight car, set to -1
		if (currentCar == NULL || (*currentCar).isEngine() ||
				(*currentCar).isFreightCar()) {
			goingLeft = -1;
			break;
		}

		goingLeft += 1;
		// When it hits a dining car, the proper distance is set
		if (currentCar->isDiningCar()) {
			break;
		}
	}
	currentCar = aTrainCar;
	// Find distance to a dining car when moving to the right
	while (true) {
		currentCar = currentCar->next;
		// If it hit a engine or freight car, set to -1
		if (currentCar == NULL || (*currentCar).isEngine() ||
				(*currentCar).isFreightCar()) {
			goingRight = -1;
			break;
		}
		goingRight += 1;
		// When it hits a dining car, the proper distance is set
		if (currentCar->isDiningCar()) {
			break;
		}
	}
	// Return the proper values given distances on the left and right
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
// Returns the distance to the closest engine to any sleeper car
int ClosestEngineToSleeperCar(TrainCar* aTraincar) {
	int minDistance = -1;
	if (aTraincar == NULL) {
		return -1;
	}
	// Loop through until you find the sleeper car
	while (aTraincar != NULL) {
		if (aTraincar->isSleepingCar()) {
			// Get the distance to the closest engine
			int currentDistance = CurrentDistanceToEngineCar(aTraincar);
			if ((currentDistance != -1 && currentDistance < minDistance) ||
					(currentDistance != -1 && minDistance == -1)) {
				minDistance = currentDistance;
			}
		}
		aTraincar = aTraincar->next;
	}
	// Return the minimum distance
	return minDistance;
}
// Get the distance to a engine car
int CurrentDistanceToEngineCar(TrainCar* aTraincar) {
	int goingLeft = 0;
	int goingRight = 0;
	TrainCar* currentCar = aTraincar;
	// Find the distance to the closest engine on the left
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
	// find the distance to the closest engine on the right
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
	// Get the minimum distance on either the left or the right
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
// Ship Freight algorithm
std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines, 
		TrainCar*& all_freight, float min_speed, int max_cars_per_train) {
	// Create a vector of traincar pointers
	std::vector<TrainCar*> allTrains;
	// Create the first train
	allTrains.push_back(NULL);
	// Set base variables
	int currentTrain = 0;
	int currentTrainLength = 0;
	// Create a loop (will break out under some conditions)
	while (true) {
		// Calculate the current speed of the train
		float currentSpeed = CalculateSpeed(allTrains[currentTrain]);
		float possibleSpeed = 0;
		if (all_freight != NULL) {
			// calculate the speed of the train if the next car is added
			possibleSpeed = CalculatePossibleSpeed(allTrains[currentTrain], all_freight);
		}
		// Conditions to go to next train are
		// If youve reached the max number of train cars
		// or you have 1 less than the max traincars and adding another 
		// would put you under the minimum speed
		// And there is another engine and freight car
		if (((currentTrainLength == max_cars_per_train) || 
					(currentTrainLength == max_cars_per_train - 1 
					 && possibleSpeed <= min_speed && !(currentSpeed < min_speed))) 
				&& (all_freight != NULL && all_engines != NULL)) {
			// Create a new train and set values to point to it
			allTrains.push_back(NULL);
			currentTrain += 1;
			currentTrainLength = 0;
			continue;
		}
		// Conditions to see if you can add another freight car
		if ((currentSpeed > min_speed && all_freight != NULL &&
					currentTrainLength != max_cars_per_train)
				&& (possibleSpeed >= min_speed || (all_engines != NULL
						&& currentTrainLength <= max_cars_per_train - 2))) {
			// Get a pointer to the next freight car
			TrainCar* nextFreightCar = all_freight;
			// Disconnect the next freight car from the freight car train
			DisconnectFromTrain(nextFreightCar, all_freight);
			// Push back the freight car to the proper train
			PushBack(allTrains[currentTrain], nextFreightCar);
			// Increment train length
			currentTrainLength += 1;
		// Conditions to see if you can add another engine car
		} else if (currentSpeed <= min_speed && all_engines != NULL &&
				currentTrainLength != max_cars_per_train) {
			// Get a pointer to the next engine
			TrainCar* nextEngine = all_engines;
			// Disconnect the engine from the engine train
			DisconnectFromTrain(nextEngine, all_engines);
			// Add the engine to to the train in the proper spot (at the end of the section of all engines in the train)
			AddEngine(allTrains[currentTrain], nextEngine);
			// Increment train length
			currentTrainLength += 1;
		} else {
			// If you cant add another engine or freight car, and you cant go to the next train, break out of the loop
			break;
		}
	}
	// Return the vector of all new trains
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
// Disconnects a traincar from the train
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
// Separate Algorithm
void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3) {
	// Set the new trains to null
	train2 = NULL;
	train3 = NULL;
	// Get base variables
	float originalSpeed = CalculateSpeed(train1);
	int total_weight, num_engines, num_freight_cars, 
		num_passenger_cars, num_dining_cars, num_sleeping_cars;
	TotalWeightAndCountCars(train1, total_weight, num_engines, 
			num_freight_cars, num_passenger_cars, 
			num_dining_cars, num_sleeping_cars);
	int originalTrainCars = num_passenger_cars + num_dining_cars + num_sleeping_cars;
	int smallerTrainEngines = (int)(num_engines/2);
	int largerTrainEngines = num_engines - smallerTrainEngines;
	int smallerTrainCars = std::round((562.5*(float)smallerTrainEngines/originalSpeed)
			- (3*smallerTrainEngines));
	int largerTrainCars = originalTrainCars - smallerTrainCars;
	TrainCar* startOfTrain = train1;
	TrainCar* endOfTrain = train1;
	// Get a pointer to the last traincar
	while(endOfTrain->next != NULL) {
		endOfTrain = endOfTrain->next;
	}
	// If the cost of the separate would not be 1
	if(!CostWouldBeOne(startOfTrain, endOfTrain, smallerTrainEngines, 
				smallerTrainCars, largerTrainEngines, largerTrainCars)) {
		int tempEngines, tempCars;
		TrainCar* closestEngine;
		bool completed = false;
		CountForward(startOfTrain, smallerTrainEngines+smallerTrainCars-1,
				tempEngines, tempCars);
		// Check if the front is just missing 1 engine
		if (tempCars == smallerTrainCars && tempEngines == smallerTrainEngines - 1) {
			// Find the closestEngine to it
			closestEngine = ClosestEngineOnRight(startOfTrain, 
					smallerTrainCars+smallerTrainEngines-1);
			DisconnectFromTrain(closestEngine, startOfTrain);
			TrainCar* tempCar1 = startOfTrain;
			int count = 1;
			while (count < smallerTrainCars+smallerTrainEngines-1) {
				tempCar1 = tempCar1->next;
				count++;
			}
			TrainCar* tempCar2 = tempCar1->next;
			// Move the closest engine one to the right of the section of cars that 
			// would make it a separatable train (now would only require 1 unlink cost)
			Insert(closestEngine, tempCar1, tempCar2);
			completed = true;
		}
		CountForward(startOfTrain, largerTrainEngines+largerTrainCars-1, 
				tempEngines, tempCars);
		// Check if the front is just missing 1 engine
		if (tempCars == largerTrainCars && tempEngines == 
				largerTrainEngines - 1 && !completed) {
			// Find the closestEngine to it
			closestEngine = ClosestEngineOnRight(startOfTrain, 
					largerTrainCars+largerTrainEngines-1);
			DisconnectFromTrain(closestEngine, startOfTrain);
			TrainCar* tempCar1 = startOfTrain;
			int count = 1;
			while (count < largerTrainCars+largerTrainEngines-1) {
				tempCar1 = tempCar1->next;
				count++;
			}
			TrainCar* tempCar2 = tempCar1->next;
			// Move the closest engine one to the right of the section of cars that 
			// would make it a separatable train (now would only require 1 unlink cost)
			Insert(closestEngine, tempCar1, tempCar2);
			completed = true;
		}
		CountBackward(endOfTrain, smallerTrainEngines+smallerTrainCars-1, 
				tempEngines, tempCars);
		// Check if the back is just missing 1 engine
		if (tempCars == smallerTrainCars && tempEngines == 
				smallerTrainEngines - 1 && !completed) {
			// Find the closestEngine to it
			closestEngine = ClosestEngineOnLeft(endOfTrain, 
					smallerTrainCars+smallerTrainEngines-1);
			DisconnectFromTrain(closestEngine, startOfTrain);
			TrainCar* tempCar1 = endOfTrain;
			int count = 0;
			while (count < smallerTrainCars+smallerTrainEngines-1) {
				tempCar1 = tempCar1->prev;
				count++;
			}
			TrainCar* tempCar2 = tempCar1->next;
			// Move the closest engine one to the left of the section of cars that 
			// would make it a separatable train (now would only require 1 unlink cost)
			Insert(closestEngine, tempCar1, tempCar2);
			completed = true;
		}
		CountBackward(endOfTrain, largerTrainEngines+largerTrainCars-1, tempEngines, tempCars);
		// Check if the back is just missing 1 engine
		if (tempCars == largerTrainCars && tempEngines == largerTrainEngines - 1 && !completed) {
			// Find the closestEngine to it
			closestEngine = ClosestEngineOnLeft(endOfTrain, largerTrainCars+largerTrainEngines-1);
			DisconnectFromTrain(closestEngine, startOfTrain);
			TrainCar* tempCar1 = endOfTrain;
			int count = 0;
			while (count < largerTrainCars+largerTrainEngines-1) {
				tempCar1 = tempCar1->prev;
				count++;
			}
			TrainCar* tempCar2 = tempCar1->next;
			// Move the closest engine one to the left of the section of cars that 
			// would make it a separatable train (now would only require 1 unlink cost)
			Insert(closestEngine, tempCar1, tempCar2);
			completed = true;
		}
	}
	// Create a loop
	while(true) {
		int tempEngines, tempCars;
		// If the pointer in the front of the train isnt null
		if (startOfTrain != NULL) {
			CountForward(startOfTrain, smallerTrainEngines + smallerTrainCars, tempEngines, tempCars);
			// Check if the front pointer is the start of a section that can be 
			// separated easily to have a low cost
			if (tempEngines == smallerTrainEngines && tempCars == smallerTrainCars) {
				// Place cars into lists
				PlaceForward(train1, startOfTrain, smallerTrainEngines + smallerTrainCars, train2, train3);
				break;
			}
			CountForward(startOfTrain, largerTrainEngines + largerTrainCars, tempEngines, tempCars);
			// Check if the front pointer is the start of a section that can be 
			// separated easily to have a low cost
			if (tempEngines == largerTrainEngines && tempCars == largerTrainCars) {
				PlaceForward(train1, startOfTrain, largerTrainEngines + largerTrainCars, train2, train3);
				// Place cars into lists
				break;
			}
			// Increment the front pointer forward one spot
			startOfTrain = startOfTrain->next;
		} else if (endOfTrain != NULL) {
			CountBackward(startOfTrain, smallerTrainEngines + smallerTrainCars, tempEngines, tempCars);
			// Check if the back pointer is the end of a section that can be 
			// separated easily to have a low cost
			if (tempEngines == smallerTrainEngines && tempCars == smallerTrainCars) {
				PlaceBackward(train1, startOfTrain, smallerTrainEngines + smallerTrainCars, train2, train3);
				// Place cars into lists
				break;
			}
			CountBackward(startOfTrain, largerTrainEngines + largerTrainCars, tempEngines, tempCars);
			// Check if the back pointer is the end of a section that can be 
			// separated easily to have a low cost
			if (tempEngines == largerTrainEngines && tempCars == largerTrainCars) {
				PlaceBackward(train1, startOfTrain, largerTrainEngines + largerTrainCars, train2, train3);
				// Place cars into lists
				break;
			}
			// Decrement the back pointer backward one spot
			endOfTrain = endOfTrain->prev;
		}
		// break out of the while loop if start of train or end of train are null
		if (startOfTrain == NULL || endOfTrain == NULL) {
			break;
		}
	}
	return;
}
// Counts the number of engines and cars that are num spaces in front of it
void CountForward(TrainCar* train, int num, int& numEngines, int& numCars) {
	int currentCount = 0;
	numEngines = 0;
	numCars = 0;
	if (train == NULL) {
		return;
	}
	// keep a count of the spaces that have been checked
	while(currentCount < num) {
		// Increment counters based on current cars value
		if (train->isEngine()) {
			numEngines++;
		} else {
			numCars++;
		}
		// Move pointer forward one spot
		if (train->next != NULL) {
			train = train->next;
		} else {
			break;
		}
		// Increment the counter
		currentCount++;
	}
	return;
}
// Counts the number of engines and cars that are num spaces behind it
void CountBackward(TrainCar* train, int num, int& numEngines, int& numCars) {
	int currentCount = 0;
	numEngines = 0;
	numCars = 0;
	if (train == NULL) {
		return;
	}
	// keep a count of the spaces that have been checked
	while(currentCount < num) {
		if (train->isEngine()) {
			numEngines++;
		} else {
			numCars++;
		}
		// Move pointer backward one spot
		if (train->prev != NULL) {
			train = train->prev;
		} else {
			break;
		}
		// Increment the counter
		currentCount++;
	}
	return;
}
// Place num number of cars in the correct train
void PlaceForward(TrainCar*& startOfTrain, TrainCar* breakStart, 
		int num, TrainCar*& train1, TrainCar*& train2) {
	for (int i=0; i<num; i++) {
		// Get a pointer to the train that you are removing
		TrainCar* tempTrain = breakStart;
		// Move breakStart to the next car
		breakStart = breakStart->next;
		// Disconnect tempTrain from the train
		DisconnectFromTrain(tempTrain, startOfTrain);
		// Push tempTrain to the end of train1
		PushBack(train1, tempTrain);
	}
	// Set train2 to whatever is left over in the original train
	train2 = startOfTrain;
	// set the original train to null
	startOfTrain = NULL;
}
// Place num number of cars in the correct train
void PlaceBackward(TrainCar*& startOfTrain, TrainCar* breakStart, 
		int num, TrainCar*& train1, TrainCar*& train2) {
	for (int i=0; i<num; i++) {
		// Get a pointer to the train that you are removing
		TrainCar* tempTrain = breakStart;
		// Move breakStart to the previous car
		breakStart = breakStart->prev;
		// Disconnect tempTrain from the train
		DisconnectFromTrain(tempTrain, startOfTrain);
		// Push tempTrain to the front of train1
		PushFront(train1, tempTrain);
	}
	// Set train2 to whatever is left over in the original train
	train2 = startOfTrain;
	// set the original train to null
	startOfTrain = NULL;
}
// Check if the separate function can be done in cost of 1
bool CostWouldBeOne(TrainCar* start, TrainCar* end, int enginesOne, 
		int carsOne, int enginesTwo, int carsTwo) {
	int numEngines, numCars;
	// Count the number of cars needed for the smaller train in the front
	CountForward(start, enginesOne + carsOne, numEngines, numCars);
	// If it matches what is needed, return true
	if (numEngines == enginesOne && numCars == carsOne) {
		return true;
	}
	// Count the number of cars needed for the larger train in the front
	CountForward(start, enginesTwo + carsTwo, numEngines, numCars);
	// If it matches what is needed, return true
	if (numEngines == enginesTwo && numCars == carsTwo) {
		return true;
	}
	// Count the number of cars needed for the smaller train in the back
	CountBackward(end, enginesOne + carsOne, numEngines, numCars);
	// If it matches what is needed, return true
	if (numEngines == enginesOne && numCars == carsOne) {
		return true;
	}
	// Count the number of cars needed for the larger train in the back
	CountBackward(end, enginesTwo + carsTwo, numEngines, numCars);
	// If it matches what is needed, return true
	if (numEngines == enginesTwo && numCars == carsTwo) {
		return true;
	}
	return false;
}
// Find the closest engine on the right of the specified car index
TrainCar* ClosestEngineOnRight(TrainCar* car, int numIn) {
	// Make car equal to the numIn'th TrainCar index
	for (int i=0; i<numIn; i++) {
		car = car->next;
	}
	// Loop until car is equal to an engine
	while (!(car->isEngine())) {
		car = car->next;
	}
	// Return car
	return car;
}
// Find the closest engine on the left of the specified car index
TrainCar* ClosestEngineOnLeft(TrainCar* car, int numIn) {
	// Make car equal to the numIn'th TrainCar index
	for (int i=0; i<numIn; i++) {
		car = car->prev;
	}
	// Loop until car is equal to an engine
	while (!(car->isEngine())) {
		car = car->prev;
	}
	// Return car
	return car;
}
// Insert a traincar before and after the specified traincars
void Insert(TrainCar* newCar, TrainCar* left, TrainCar* right) {
	// Set prev and next for the newCar
	newCar->prev = left;
	newCar->next = right;
	// Set newCar as the next of the previous index
	if (left != NULL) {
		left->next = newCar;
	}
	// Set newCar as the prev of the next index
	if (right != NULL) {
		right->prev = newCar;
	}
	return;
}
// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//
