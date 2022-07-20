local a: Table<string, number> = { 
    ["key"] = 123,
    ["key2"] = 124
}

-- This should not work
a["key"] = true