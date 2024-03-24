#include <random>
#include <vector>
#include "FigureType.h"

FigureData CreateFigureData(FigureType type, Color3d color)
{
	switch (type)
	{
	case FigureType::L:
		return {
			std::vector<CellData>{CellData{color, true}, {color, false}, {color, false} },
			std::vector<CellData>{CellData{color, true}, {color, false}, {color, false} },
			std::vector<CellData>{CellData{color, true}, {color, true}, {color, false} },
		};
	case FigureType::J:
		return {
			std::vector<CellData>{CellData{color, false}, {color, false}, {color, true} },
			std::vector<CellData>{CellData{color, false}, {color, false}, {color, true} },
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, true} },
		};
	case FigureType::O:
		return {
			std::vector<CellData>{CellData{color, true}, {color, true}, },
			std::vector<CellData>{CellData{color, true}, {color, true}, },

		};
	case FigureType::I:
		return {
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, false}, {color, false} },
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, false}, {color, false} },
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, false}, {color, false} },
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, false}, {color, false} },
		};
	case FigureType::S:
		return {
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, true} },
			std::vector<CellData>{CellData{color, true}, {color, true}, {color, false} },
			std::vector<CellData>{CellData{color, false}, {color, false}, {color, false} },
		};
	case FigureType::Z:
		return {
			std::vector<CellData>{CellData{color, true}, {color, true}, {color, false} },
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, true} },
			std::vector<CellData>{CellData{color, false}, {color, false}, {color, false} },
		};
	case FigureType::A:
		return {
			std::vector<CellData>{CellData{color, false}, {color, true}, {color, false} },
			std::vector<CellData>{CellData{color, true}, {color, true}, {color, true} },
			std::vector<CellData>{CellData{color, false}, {color, false}, {color, false} },
		};
	default:
		throw std::exception("unknown figure type");
	};
}

FigureType GetRandomFigureType()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector <FigureType> allFigures {
		FigureType::A,
		FigureType::I,
		FigureType::J,
		FigureType::L,
		FigureType::O,
		FigureType::S,
		FigureType::Z,
	};
	std::uniform_int_distribution<size_t> dis(0, allFigures.size() - 1);

	return allFigures[dis(gen)];
}