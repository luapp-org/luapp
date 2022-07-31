-- This should break and throw an error
local myFunction: (number, string): any = function (a: boolean, b: string): any 
    -- Do some stuff idk
end

-- This should work (just showing a different way to define the functions)
local function func(a: number, b: string): boolean 
    -- Do some more stuff (need to add return type checker)
end