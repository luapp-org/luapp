local a: Table<string, any> = { 
    ["key"] = 123,
    ["key2"] = 124
}

-- This should work, since table has all values as any type
a["key"] = true