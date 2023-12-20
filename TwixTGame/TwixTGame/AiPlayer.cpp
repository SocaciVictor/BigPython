#include "AiPlayer.h"
#include <stdexcept>
#include <limits>
#include <fstream>
#include <unordered_set>

void AiPlayer::loadPolicy()
{
	std::ifstream input{ m_dataFile };
	if (input.bad())
		throw std::runtime_error("Error input file");

	std::string hash;
	float value;
	while (!input.eof()) {
		input >> hash >> value;
		m_stateMoveCosts.insert(std::make_pair(hash, value));
	}
	input.close();
}

void AiPlayer::savePolicy()
{
	std::ofstream output{ m_dataFile , std::ios::trunc};
	if (output.bad())
		throw std::runtime_error("Error output file");
	for (const auto& moveState : m_stateMoveCosts) {
		if (moveState.second != initialEstimation) {
			if (!moveState.first.empty())
				output << moveState.first << ' ' << moveState.second << "\n";
		}
	}
	output.close();
}

std::vector<std::unique_ptr<Move>> AiPlayer::generateMoveCollection()
{
	std::vector<std::unique_ptr<Move>> moves;
	PieceType pieceType;
	//generate all posible pillar moves
	if (!m_moved) {
		switch (m_color) {
		case PieceColor::Blue:
			pieceType = PieceType::BluePillar;
			break;
		case PieceColor::Red:
			pieceType = PieceType::RedPillar;
			break;
		}
 		for (const auto& line : m_board.getData()) {
 			for (const auto& base : line) {
				if (base) {
					//if base is not occupied by pillar
					if (base->getColor() == PieceColor::None) {
						//is not in enemy base
						if (m_color == PieceColor::Blue &&
							(base->getCoordinates().x == 0 || base->getCoordinates().x == m_board.getColumns() - 1)) continue;
						if (m_color == PieceColor::Red &&
							(base->getCoordinates().y == 0 || base->getCoordinates().y == m_board.getRows() - 1)) continue;

						moves.emplace_back(std::make_unique<MovePillar>(base->getCoordinates(), pieceType));
					}
				}
				
			}
		}
	}
	//generate posible bridge moves
	else {
		switch (m_color) {
		case PieceColor::Blue:
			pieceType = PieceType::BlueBridge;
			break;
		case PieceColor::Red:
			pieceType = PieceType::RedBridge;
			break;
		}
		

		//generate all the delete moves
		//for (const auto& bridge : m_board.getBridges()) {
		//	//check if bridge belongs to player
		//	if(bridge.second.getColor() == m_color)
		//		moves.emplace_back(std::make_unique<MoveBridge>(bridge.first.point1, bridge.first.point2, MoveType::Delete, pieceType));
		//}
		//generate all the additive moves
		uint8_t dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
		uint8_t dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
		uint8_t x, y, nextX, nextY;
		std::unordered_set<TwoPoint, TwoPointHash> bridgePoints;
		for (const auto& line : m_board.getData()) {
			for (const auto& base : line) {
				if (base) {
					if (base->getColor() != PieceColor::None) {
						//check if pillar belongs to player
						if (static_cast<Pillar*>(base.get())->getColor() != m_color)
							continue;
						x = base->getCoordinates().x;
						y = base->getCoordinates().y;
						for (uint8_t i = 0; i < 8; ++i) {
							nextX = x + dx[i];
							nextY = y + dy[i];
							//check if potential pillar is outside the board
							if (!m_board.isInBoard(Point{ nextX, nextY }))
								continue;
							//check if found base is pillar
							if (dynamic_cast<Pillar*>(m_board.getData()[nextY][nextX].get()) != nullptr) {
								//check if found base belongs to player
								if (static_cast<Pillar*>(m_board.getData()[nextY][nextX].get())->getColor() != m_color)
									continue;
								//check if the bridge was checked
								Point start{ Point{x,y} };
								Point end{ Point{nextX,nextY} };
								if (end < start)
									std::swap(start, end);
								if (bridgePoints.find(TwoPoint{ start,end }) != bridgePoints.end())
									continue;
								//check for inersections
								if (m_board.isNotIntersection(Point{ x,y }, Point{ nextX, nextY })) {
									moves.emplace_back(std::make_unique<MoveBridge>(Point{ x,y }, Point{ nextX, nextY }, MoveType::Add, pieceType));
									bridgePoints.insert(TwoPoint{ start, end });
								}
									
							}
						}
					}
				}
			}
		}
		//generete end turn move
		moves.emplace_back(std::make_unique<MoveBridge>(Point{ 0,0 }, Point{ 0, 0 }, MoveType::Next, pieceType));
	}
	return moves;
}

AiPlayer::AiPlayer(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color,
	const std::string& dataFile, Board& board)
	: Player{ number_pillars, number_bridges, color }, m_dataFile{ dataFile }, m_board{board}
{
	//loadPolicy();
}

AiPlayer::~AiPlayer()
{
	//savePolicy();
}

//caller responsible for ownership
std::unique_ptr<Move> AiPlayer::getNextMove(bool randomMoves)
{
	std::vector<std::unique_ptr<Move>> possibleMoves{ generateMoveCollection() };
	
	//only enters when no possible moves => draw
	if (possibleMoves.empty())
		return nullptr;

	//if a bridge can be placed it should be placed
	MoveBridge* moveBridge = dynamic_cast<MoveBridge*>(possibleMoves.front().get());
	if (moveBridge) {
		if (possibleMoves.size() > 1)
			possibleMoves.pop_back();
	}

	uint64_t moveIndex{ 0 };
	std::string bestStateMoveHash{ "" };
	//to change bernDist chance
	std::bernoulli_distribution bernDist(explorationRate); //exploration

	//randomly picked move
	if (bernDist(randomEngine) && randomMoves) {
		std::uniform_int_distribution<uint64_t> intDist(0, (uint64_t)possibleMoves.size() - 1);
		moveIndex = intDist(randomEngine);
		bestStateMoveHash = m_board.getHashWithMove(possibleMoves[moveIndex].get());
		m_stateMoveCosts.insert(std::make_pair( bestStateMoveHash, initialEstimation ));
	}
	//select best action available
	else {
		float bestMoveEstimation = -std::numeric_limits<float>::infinity();
		for (uint64_t i = 0; i < possibleMoves.size(); ++i) {
			std::string stateMoveHash = m_board.getHashWithMove(possibleMoves[i].get());

			//map(std::pair<std::string, float>, bool)
			//float part is the current move value map.first->second
			auto map = m_stateMoveCosts.insert(std::make_pair(stateMoveHash, initialEstimation));

			if (map.first->second > bestMoveEstimation) {
				moveIndex = i;
				bestStateMoveHash = stateMoveHash;
				bestMoveEstimation = map.first->second;
			}
		}
	}
	//contains all the moves so far
	m_previousStateMoves.emplace_back(bestStateMoveHash);

	//return move
	//pillar move
	MovePillar* ptr = dynamic_cast<MovePillar*>(possibleMoves[moveIndex].get());
	if (ptr) 
		return std::make_unique<MovePillar>(ptr->pozition, (PieceType)ptr->type);
	//bridge move
	MoveBridge* ptrBridge = static_cast<MoveBridge*>(possibleMoves[moveIndex].get());
	return std::make_unique<MoveBridge>(ptrBridge->startPozition, ptrBridge->endPozition, (MoveType)ptrBridge->moveType, (PieceType)ptrBridge->type);

}

void AiPlayer::feedReward(float target)
{
	for (auto it = m_previousStateMoves.rbegin(); it != m_previousStateMoves.rend(); ++it) {
		const auto& stateMove = *it;
		float& estimation = m_stateMoveCosts[stateMove];
		estimation = estimation + learningRate * (target - estimation);
		target = estimation;
	}
	m_previousStateMoves.clear();
}

uint64_t AiPlayer::getStateSize() const noexcept
{
	uint64_t count = 0;
	for (const auto& value : m_stateMoveCosts)
		if (value.second != initialEstimation)
			count++;
	return count;
}
