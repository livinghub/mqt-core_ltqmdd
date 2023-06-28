from typing import Any, Optional, overload
from enum import Enum
import mqt.core._core

class OpType:
    """
    <attribute '__doc__' of 'OpType' objects>
    """

    @entries: dict
    
    def __init__(*args, **kwargs):
        """
        Initialize self.  See help(type(self)) for accurate signature.
        """
        ...
    
    barrier: OpType
    
    classiccontrolled: OpType
    
    compound: OpType
    
    dcx: OpType
    
    ecr: OpType
    
    gphase: OpType
    
    h: OpType
    
    i: OpType
    
    iswap: OpType
    
    measure: OpType
    
    none: OpType
    
    peres: OpType
    
    peresdag: OpType
    
    phase: OpType
    
    reset: OpType
    
    rx: OpType
    
    rxx: OpType
    
    ry: OpType
    
    ryy: OpType
    
    rz: OpType
    
    rzx: OpType
    
    rzz: OpType
    
    s: OpType
    
    sdag: OpType
    
    showprobabilities: OpType
    
    snapshot: OpType
    
    swap: OpType
    
    sx: OpType
    
    sxdag: OpType
    
    t: OpType
    
    tdag: OpType
    
    teleportation: OpType
    
    u2: OpType
    
    u3: OpType
    
    v: OpType
    
    vdag: OpType
    
    x: OpType
    
    xx_minus_yy: OpType
    
    xx_plus_yy: OpType
    
    y: OpType
    
    z: OpType
    
def add(a: int, b: int) -> int:
    ...

barrier: OpType

classiccontrolled: OpType

compound: OpType

dcx: OpType

ecr: OpType

gphase: OpType

h: OpType

i: OpType

iswap: OpType

measure: OpType

none: OpType

def optype_from_string(arg: str, /) -> mqt.core._core.OpType:
    ...

peres: OpType

peresdag: OpType

phase: OpType

reset: OpType

rx: OpType

rxx: OpType

ry: OpType

ryy: OpType

rz: OpType

rzx: OpType

rzz: OpType

s: OpType

sdag: OpType

showprobabilities: OpType

snapshot: OpType

swap: OpType

sx: OpType

sxdag: OpType

t: OpType

tdag: OpType

teleportation: OpType

u2: OpType

u3: OpType

v: OpType

vdag: OpType

x: OpType

xx_minus_yy: OpType

xx_plus_yy: OpType

y: OpType

z: OpType

