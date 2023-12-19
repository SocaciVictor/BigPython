#include "AiPlayer.h"

void AiPlayer::loadPolicy()
{
}

void AiPlayer::savePolicy()
{
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
				//if base is not occupied by pillar
				if (dynamic_cast<Pillar*>(base.get()) == nullptr) {
					moves.emplace_back(std::make_unique<MovePillar>(base->getCoordinates(), pieceType));
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
		for (const auto& bridge : m_board.getBridges()) {
			moves.emplace_back(std::make_unique<MoveBridge>(bridge.first.point1, bridge.first.point2, MoveType::Delete, pieceType));
		}
		//generate all the additive moves
		uint8_t dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
		uint8_t dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
		uint8_t x, y, nextX, nextY;
		for (const auto& line : m_board.getData()) {
			for (const auto& base : line) {
				if (dynamic_cast<Pillar*>(base.get()) != nullptr) {
					x = base->getCoordinates().x;
					y = base->getCoordinates().y;
					for (uint8_t i = 0; i < 8; ++i) {
						nextX = x + dx[i];
						nextY = y + dy[i];
						//check if potential pillar is outside the board
						if (!m_board.isInBoard(Point{nextX, nextY}))
							continue;
						//check if found base is pillar
						if (dynamic_cast<Pillar*>(m_board.getData()[nextY][nextX].get()) != nullptr) {
							//check for inersections
							if (m_board.isNotIntersection(Point{ x,y }, Point{ nextX, nextY }))
								moves.emplace_back(std::make_unique<MoveBridge>(Point{ x,y }, Point{ nextX, nextY }, MoveType::Add, pieceType));
						}
					}
				}
			}
		}
	}
	return moves;
}

AiPlayer::AiPlayer(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color,
	const std::string& dataFile, Board& board)
	: Player{ number_pillars, number_bridges, color }, m_dataFile{ dataFile }, m_board{board}
{
	loadPolicy();
}

AiPlayer::~AiPlayer()
{
	savePolicy();
}
