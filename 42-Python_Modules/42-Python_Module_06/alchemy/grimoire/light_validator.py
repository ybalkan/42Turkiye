def validate_ingredients(ingredients: str) -> str:
    from . import light_spellbook
    allowed = light_spellbook.light_spell_allowed_ingredients()
    ingredients_lower = ingredients.lower()
    for item in allowed:
        if item in ingredients_lower:
            return "VALID"
    return "INVALID"
