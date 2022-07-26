local test: boolean = false

for a: number in { 1, 2, 3 } do 
    -- This should work
    local secondTest: boolean = test
end

-- This should not work
local canIReference: number = secondTest