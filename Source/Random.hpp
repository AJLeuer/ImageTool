//
//  Random.hpp
//  
//
//  Created by Adam James Leuer on 6/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#pragma once
/* The classes below are exported */
#pragma GCC visibility push(default)

#include <iostream>
#include <limits>
#include <random>
#include <cmath>
#include <thread>

using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::thread;

template<typename N>
class FastRand {

protected:

	std::random_device dev ;
	std::uniform_int_distribution<N> dist ;
    std::default_random_engine rndm = std::default_random_engine(dev()) ;

	const N minimum ;
	const N maximum ;
    
    public:

	/* A conveniance random object that won't require initialization.
	 * Especially useful in constructors and initializing static values.
	 * A superior replacement for calling rand()
	 */
	static FastRand defaultRandom ;

	FastRand(N _min, N _max) ;

	FastRand(const FastRand<N> & other) ;

    template<typename M>
    FastRand(const FastRand<M> & other) ;

	FastRand & operator=(const FastRand<N> & rhs) ;
	~FastRand() ;
	N nextValue() ;
	N nextValue(N minimum, N maximum) ;
	template<typename R> R nextValue(R _min, R _max) ;
	N operator()() ;
	N operator()(N minimum, N maximum) ;
    N getMax() const { return this->maximum; }
    N getMin() const { return this->minimum; }

} ;

template<>
class FastRand<float> {

protected:

	std::random_device dev ;
	std::uniform_real_distribution<float> dist ;
	std::default_random_engine rndm = std::default_random_engine(dev()) ;

	float minimum ;
	float maximum ;


public:

	static FastRand defaultRandom ;
	static FastRand * randPositionSetter ;

	FastRand(float _min, float _max) ;
	FastRand(const FastRand<float> & other) ;
	FastRand & operator=(const FastRand<float> & rhs) ;
	~FastRand() ;
	float nextValue() ;
	float nextValue(float minimum, float maximum) ;
	template<typename R> R nextValue(R _min, R _max) ;
	float operator()() ;
	float operator()(float minimum, float maximum) ;


} ;

template<>
class FastRand<double> {

protected:
	
	static FastRand<double> defaultRandom ;

	std::random_device dev ;
	std::uniform_real_distribution<double> dist ;
	std::default_random_engine rndm = std::default_random_engine(dev()) ;

	double minimum ;
	double maximum ;

	
public:



	FastRand(double _min, double _max) ;
	FastRand(const FastRand<double> & other) ;
	FastRand & operator=(const FastRand<double> & rhs) ;
	~FastRand() ;
	double nextValue() ;
	double nextValue(double minimum, double maximum) ;
	template<typename R> R nextValue(R _min, R _max) ;
	double operator()() ;
	double operator()(double minimum, double maximum) ;


} ;

template<typename N>
FastRand<N>::FastRand(N _min, N _max) :
	minimum(_min),
	maximum(_max)
{
	//dev ;
	dist = uniform_int_distribution<N>(minimum, maximum) ;
	rndm.seed(dev()) ;
}

template<typename N>
FastRand<N>::FastRand(const FastRand<N> & other) :
    maximum(other.maximum),
    minimum(other.minimum)
{
	std::random_device dev2 ;
	dist = uniform_int_distribution<N>(other.minimum, other.maximum) ;
	rndm.seed(dev2()) ;
}

template<typename N>
template<typename M>
FastRand<N>::FastRand(const FastRand<M> & other) {
    this->minimum(static_cast<N>(other.minimum)) ;
    this->maximum(static_cast<N>(other.maximum)) ;

    dist = uniform_int_distribution<N>(minimum, maximum) ;
	rndm.seed(dev()) ;
}

template<typename N>
FastRand<N>::~FastRand(){}

template<typename N>
FastRand<N> & FastRand<N>::operator=(const FastRand<N> & rhs)
{
	if (this != &rhs) {
		std::random_device dev2 ;
		dist = uniform_int_distribution<N>(rhs.minimum, rhs.maximum) ;
		rndm.seed(dev2()) ;
	}
	return *this ;
}

template<typename N>
N FastRand<N>::nextValue() {
	return dist(rndm) ;
}

template<typename N>
N FastRand<N>::nextValue(N minimum, N maximum) {
	std::uniform_int_distribution<N> dif_dist{minimum, maximum} ;
	return dif_dist(rndm) ;
}

template<typename N>
N FastRand<N>::operator()() {
	return nextValue() ;
}

template<typename N>
N FastRand<N>::operator()(N minimum, N maximum) {
	return nextValue(minimum, maximum) ;
}

template<typename N>
template<typename R>
R FastRand<N>::nextValue(R _min, R _max) {
	std::uniform_int_distribution<R> dif_dist{_min, _max} ;
	return dif_dist(rndm) ;
}

template<typename N>
FastRand<N> FastRand<N>::defaultRandom(std::numeric_limits<N>::min(), std::numeric_limits<N>::max()) ;


/* more useful random functions: */
template<typename N>
N randSignFlip(N n) {

	FastRand<unsigned short> rand(0, 1) ;
	bool pos = rand.nextValue() % 2 ;
	if (pos) {
		return n ;
	}
	else {
		return (n * -1) ;
	}

}

template <typename T>
T chooseAtRand(T t1, T t2) {
	FastRand<unsigned long> rand(0, 1) ;
	bool first = rand.nextValue() ;
	if (first) {
		return t1 ;
	}
	else {
		return t2 ;
	}
}

/**
 * Returns a random enumeration of enum type
 * SomeEnum. SomeEnum should ideally use integer values starting
 * at zero as the underlying value for its enumerations.
 *
 * @tparam SomeEnum An enumeration type
 * @tparam N Some integer or floating point type
 * @param maximum The numerical value of the maximum enum of type SomeEnum
 */
template<typename SomeEnum, typename N>
SomeEnum randomEnumeration(N maximum) {

	FastRand<N> randm(0, maximum) ;
	N num = randm() ;
	return SomeEnum(num) ;
}

#pragma GCC visibility pop
