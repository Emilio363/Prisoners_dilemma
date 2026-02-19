using Images

# ATTENTION: each strategy have to return 'C' or 'D'

function cooperate()::Char
    return 'C'
end

function defect()::Char
    return 'D'
end

function strategyColor(strategy::Function)::RGB
    color = RGB(0,0,0)
    if strategy == cooperate
        color = RGB(0.5,1.0,1.0)
    elseif strategy == defect
        color = RGB(0.5,0.2,0.2)
    else
        color = RGB(1,0,0)
    end
    return color
end