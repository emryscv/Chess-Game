#pragma once
#include "Piece.h"
class Rook : public Piece{
public:
    Rook(Color color) : Piece(color) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(int originX, int originY, int destinationX, int destinationY) const override;
};

