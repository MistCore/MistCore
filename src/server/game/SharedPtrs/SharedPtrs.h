#ifndef SHARED_PTRS_H
# define SHARED_PTRS_H

class Aura;
class UnitAura;
class AuraEffect;

# define CAST(x,y) std::dynamic_pointer_cast<x>(y)
# define CONST_CAST(x, y) std::const_pointer_cast<const x>(y)

# define AuraPtr std::shared_ptr<Aura>
# define constAuraPtr std::shared_ptr<const Aura>
# define UnitAuraPtr std::shared_ptr<UnitAura>
# define AuraEffectPtr std::shared_ptr<AuraEffect>
# define constAuraEffectPtr std::shared_ptr<const AuraEffect>

# define TO_UNITAURA(y) CAST(UnitAura,y)

# define NULLAURA AuraPtr()
# define NULLAURA_EFFECT AuraEffectPtr()


#endif /* !SHARED_PTRS_H */