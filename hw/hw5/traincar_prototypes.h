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
#include "traincar.h"
#include <vector>
void PushBack(TrainCar*& aTraincar, TrainCar* bTraincar);
void DeleteAllCars(TrainCar* aTrainCar);
void TotalWeightAndCountCars(TrainCar* train, int& total_weight,
		int& num_engines, int& num_freight_cars, int& num_passenger_cars,
		int& num_dining_cars, int& num_sleeping_cars);
void AddNumbers(TrainCar* currentCar, int& total_weight,
		int& num_engines, int& num_freight_cars, int& num_passenger_cars,
		int& num_dining_cars, int& num_sleeping_cars);
float CalculateSpeed(TrainCar* aTraincar);
float CalculatePossibleSpeed(TrainCar* aTraincar, TrainCar* bTraincar);
float AverageDistanceToDiningCar(TrainCar* aTraincar);
float CurrentDistanceToDiningCar(TrainCar* aTraincar);
int ClosestEngineToSleeperCar(TrainCar* aTraincar);
int CurrentDistanceToEngineCar(TrainCar* aTraincar);
std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines,
		TrainCar*& all_freight, float min_speed, int max_cars_per_train);
void AddEngine(TrainCar*& aTrainCar, TrainCar*& aEngineCar);
void DisconnectFromTrain(TrainCar* aTrainCar, TrainCar*& startOfTrain);
void Separate(TrainCar* train1, TrainCar*& train2, TrainCar*& train3);
void CountForward(TrainCar* train, int num, int& numEngines, int& numCars);
void CountBackward(TrainCar* train, int num, int& numEngines, int& numCars);
