// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//
// Include traincar.h to be able to take in TranCar objects
#include "traincar.h"
#include <vector>
// Push to the back of the train
void PushBack(TrainCar*& aTraincar, TrainCar* bTraincar);
// Push to the front of the train
void PushFront(TrainCar*& aTraincar, TrainCar* bTraincar);
// Delete all TrainCars in the train
void DeleteAllCars(TrainCar* aTrainCar);
// Totals up all weights and types of cars
void TotalWeightAndCountCars(TrainCar* train, int& total_weight,
		int& num_engines, int& num_freight_cars, int& num_passenger_cars,
		int& num_dining_cars, int& num_sleeping_cars);
// Adds numbers from one TrainCar to the TotalWeightAndCountCars
void AddNumbers(TrainCar* currentCar, int& total_weight,
		int& num_engines, int& num_freight_cars, int& num_passenger_cars,
		int& num_dining_cars, int& num_sleeping_cars);
// Calculate speed of the train
float CalculateSpeed(TrainCar* aTraincar);
// Calculate speed of the train if the next car is added
float CalculatePossibleSpeed(TrainCar* aTraincar, TrainCar* bTraincar);
// Average the distance to the dining car
float AverageDistanceToDiningCar(TrainCar* aTraincar);
// Get the current cars distance to a dining car
float CurrentDistanceToDiningCar(TrainCar* aTraincar);
// Get the closest engine to a sleeper car
int ClosestEngineToSleeperCar(TrainCar* aTraincar);
// Get the current distance to an engine car
int CurrentDistanceToEngineCar(TrainCar* aTraincar);
// Ship freight algorithm
std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines,
		TrainCar*& all_freight, float min_speed, int max_cars_per_train);
// Adds an engine at the end of the string of engines in the train
void AddEngine(TrainCar*& aTrainCar, TrainCar*& aEngineCar);
// Disconnects traincar from train
void DisconnectFromTrain(TrainCar* aTrainCar, TrainCar*& startOfTrain);
// Separate algorithm
void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3);
// Counts the number of engines and cars forward a certain number of TrainCars
void CountForward(TrainCar* train, int num, int& numEngines, int& numCars);
// Counts the number of engines and cars backward a certain number of TrainCars
void CountBackward(TrainCar* train, int num, int& numEngines, int& numCars);
// Handles placing cars into another train forward
void PlaceForward(TrainCar*& startOfTrain, TrainCar* breakStart, int num, TrainCar*& train1, TrainCar*& train2);
// Handles placing cars into another train backward
void PlaceBackward(TrainCar*& startOfTrain, TrainCar* breakStart, int num, TrainCar*& train1, TrainCar*& train2);
// Check if the separate can be done with a cost of 1
bool CostWouldBeOne(TrainCar* start, TrainCar* end, int enginesOne, int carsOne, int enginesTwo, int carsTwo);
// Looks for the closest engine to the right of a traincar
TrainCar* ClosestEngineOnRight(TrainCar* car, int numIn);
// Looks for the closest engine to the left of a traincar
TrainCar* ClosestEngineOnLeft(TrainCar* car, int numIn);
// Inserts a traincar between two other traincars
void Insert(TrainCar* newCar, TrainCar* left, TrainCar* right);
