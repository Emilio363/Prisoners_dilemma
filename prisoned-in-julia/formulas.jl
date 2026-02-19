include("game.jl")
#include("iperparametri.jl")

#K = iperparametri.K
#Max_memory = iperparametri.Max_memory
#Rand_Max = iperparametri.Rand_Max

function fermi(point1::Float64, point2::Float64)::Float64
    prob = 1 / (1 + exp((point1 - point2) / K))
    return prob
end

function H_x(memory::Int)::Float64
    if Max_memory == 0
        return 1
    else
        return 1-(1-beta)*memory/Max_memory
    end
end

function incrementPoint(player1::Cell, player2::Cell)::Int
    player1.point += oneGame_oneResult(player1, player2)
    return 0
end

function changeStrategy(player1::Cell, player2::Cell)
    thisrand = rand()/Rand_Max
    prob = H_x(player1.memory)*fermi(player1.point, player2.point)
    newstrategy = player1.strategy
    if prob<thisrand
        newstrategy = player2.strategy
    end
    if newstrategy == player1.strategy
        if player1.memory < Max_memory
            player1.memory +=1
        end
    else
        player1.memory = 0
        player1.strategy = newstrategy
    end
end