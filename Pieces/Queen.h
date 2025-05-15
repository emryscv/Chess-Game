#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(Color color, int x, int y) : Piece(color, x, y) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(const int& destinationX, const int& destinationY) const override;
};

