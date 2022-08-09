local num: number = 1
local str: string = "value"
local boo: boolean = false

-- Length
local a: string = #num -- ERROR
local b: string = #str

-- Minus
local c: number = -str -- ERROR
local d: number = -num

-- Not
local e: boolean = not boo