local function func(a: number, b: string): boolean
    print("some random print")
    print(a, b)
    return true
end

local function voidFun(): string
    return "str"
end

print("output: ", func(1, "a"))
print(voidFun())