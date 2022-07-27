-- Testing scopes within a simple block
local highestScope: number = 1

do
    local lowestScope: number = highestScope
end

lowestScope = 123