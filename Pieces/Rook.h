#pragma once
#include "Piece.h"
class Rook : public Piece{
public:
    Rook(Color color) : Piece(color) {}
    std::string GetRepresentation() const override;
    bool IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const override;
};

