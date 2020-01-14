### CENG211 THE2 ###

def is_firmus(block1,block2):
  x1,y1,x2,y2 = block1
  a1,b1,a2,b2 = block2


def area (x1,y1,x2,y2):
    return abs(x1-x2)*abs(y1-y2)

def overlap (x1,y1,x2,y2,a1,b1,a2,b2):
    z1 = min(x1,x2)
    z2 = max(x1,x2)
    z3 = min(a1,a2)
    z4 = max(a1,a2)
    z5 = min(y1,y2)
    z6 = max(y1,y2)
    z7 = min(b1,b2)
    z8 = max(b1,b2)
    overarea = max(0, min(z2, z4) - max(z1, z3)) * max(0, \
    min(z6,z8) - max(z5, z7))
    return area(x1,y1,x2,y2) + area(a1,b1,a2,b2) -overarea

def smallest (x1,y1,x2,y2,a1,b1,a2,b2):
    if  0.001 <= min(a1,a2) - (x1 + x2)/2:
       balance = 2*min(a1,a2) - min(x1,x2) - max(x1,x2)
       return [max(x1,x2),y1,max(x1,x2)+balance,y2]
    elif (x1+x2)/2 - max(a1,a2) >= 0.001:
      balance = min(x1,x2) + max(x1,x2) - 2*max(a1,a2)
      return [min(x1,x2),y1,min(x1,x2)-balance,y2]

 
  if abs(min(y1,y2)) < 0.001 and abs(min(b1,b2)) >= 0.001:
    if abs(max(y1,y2) - min(b1,b2)) <0.001:
      if (0.001 <= max(x1,x2) -(a1+a2)/2  and \
        0.001 <= (a1+a2)/2 - min(x1,x2)) or abs(max(x1,x2) -(a1+a2)/2)< 0.001 or \
        abs(min(x1,x2) -(a1+a2)/2)< 0.001:
        return ['FIRMUS', overlap(x1,y1,x2,y2,a1,b1,a2,b2)]
      else:
        return ['ADDENDUM', smallest(a1,b1,a2,b2,x1,y1,x2,y2)]
    else:
      return ['DAMNARE', \
      overlap(x1,y1,x2,y2,a1,b1,a2,b2)]

  
  elif abs(min(b1,b2)) < 0.001 and abs(min(y1,y2)) >= 0.001:
    if abs(max(b1,b2) - min(y1,y2)) <0.001:
      if (0.001 <= max(a1,a2) -(x1+x2)/2  and \
         0.001 <= (x1+x2)/2 - min(a1,a2)) or abs(max(a1,a2) -(x1+x2)/2)< 0.001 or \
         abs(min(a1,a2) -(x1+x2)/2)< 0.001:
         return ['FIRMUS', overlap(x1,y1,x2,y2,a1,b1,a2,b2)]
      else:
        return ['ADDENDUM', smallest (x1,y1,x2,y2,a1,b1,a2,b2)]
    else:
      return ['DAMNARE', \
      overlap(x1,y1,x2,y2,a1,b1,a2,b2)]
  
  else:
    return ['DAMNARE', \
      overlap(x1,y1,x2,y2,a1,b1,a2,b2)]







