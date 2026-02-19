include("game.jl")
include("formulas.jl")
include("strategy.jl")
include("iperparametri.jl")
using StaticArrays

#Rand_Max = iperparametri.Rand_Max

function stampStrategies(row::Int, col::Int, mat::Array{Cell,2})
    println("\n strategies: \n")
    for i in 1:row
        for j in 1:col
            val = (mat[i,j].strategy == cooperate) ? 'C' : 'D'
            println("$val ")
        end
        println("\n")  
    end
    println("\n")
end

function stamPoints(row::Int, col::Int, mat::Array{Cell,2})
    # mat have to be a matrix of Cell
    println("\n memories: \n")
    for i in 1:row
        for j in 1:col
            val = mat[i,j].memory
            println("$val")
        end
        println("\n")
    end
    println("\n")
end

function printMatrix()
    return 0
end

function randomStrategy()
    num = rand()/Rand_Max
    if num<0.5
        return cooperate
    else
        return defect
    end
end

function my_main()
    
    Cell_Matrix = Array{Cell, 2}(undef, (DIM, DIM))
    for i in 1:DIM, j in 1:DIM
        Cell_Matrix[i,j] = Cell(0, 0, randomStrategy())
    end

    Cells = SMatrix{DIM, DIM}(Cell_Matrix)
    stampStrategies(DIM, DIM, Cells)
    println("hi")
    #Cells::
end

my_main()