local a: number = 12

-- Arithmetic
local add: string = a + 1  -- This should be an error
local sub: number = a - 1
local mul: number = a * 1
local div: number = a / 1
local pow: number = a ^ 1
local mod: number = a % 1

-- Concat
local str1: string = 1 .. 1
local str2: string = "adad" .. 1223
local str3: boolean = 1 .. 1 -- There should be an error

-- Comparisons
local eq: boolean = 1 == 1
local ne: boolean = 1 ~= 1
local ge: boolean = 1 >= 1
local le: boolean = 1 <= "a" -- There should be an error

-- And + Or operations
local andTest1: number = 1 and 2
local andTest2: number = 1 and "string" -- This should error

local orTest1: number = 1 or 2
local orTest2: number = "string" or 1 -- This should error