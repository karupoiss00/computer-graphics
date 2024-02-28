#pragma once
#include <memory>
#include <string>
#include "IDrawingStrategy.h"

class IDrawingStrategyFactory
{
public:
	virtual std::shared_ptr<IDrawingStrategy> GetStrategy(std::string type) = 0;

	virtual ~IDrawingStrategyFactory(){};
};