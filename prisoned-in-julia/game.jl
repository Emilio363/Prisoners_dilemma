include("strategy.jl")
#include("iperparametri.jl")

mutable struct Cell
    point::Float64
    memory::Int
    strategy::Function
end

#R = iperparametri.R
#S = iperparametri.S
#T = iperparametri.T
#P = iperparametri.P

function neighborhoodApply(fun::Function, dimension::Int, Cells, row::Int, col::Int)
    dx = [-1,1,0,0]
    dy = [0,0,-1,1]
    for dir in 1:4
        nrow = row + dx[dir]
        ncol = col + dy[dir]
        if nrow >= 0 && nrow < dimension && ncol >= 0 && ncol < dimension
            fun(Cells[row][col], Cells[nrow][ncol])
        end
    end
end

function oneRandNeighbourApply(fun::Function, cells::Cell, row::Int, col::Int)
    dx = [-1,1,0,0]
    dy = [0,0,-1,1]
    while True
        dir = rand()%4
        nrow = row + dx[dir]
        ncol = col + dy[dir]
        if nrow >= 0 && nrow < dimension && ncol >= 0 && ncol < dimension
            fun(Cells[row][col], Cells[nrow][ncol])
        end
        cond(!(nrow >= 0 && nrow < dimension && ncol >= 0 && ncol < dimension)) || break
    end
    fun(Cells[row][col], Cells[nrow][ncol]);
end

function oneGame_oneResult(player1::Cell, player2::Cell)
    move1 = player1.strategy()
    move2 = player2.strategy()
    
    if (move1 == 'C') && (move2 == 'C')
        return R
    elseif (move1 == 'C') && (move2 == 'D')
        return S
    elseif (move1 == 'D') && (move2 == 'C')
        return T
    elseif (move1 == 'D') && (move2 == 'D')
        return P
    else
        return -1
    end
end

function colorOfCell(player::Cell)
    return strategyColor(player.strategy)
end