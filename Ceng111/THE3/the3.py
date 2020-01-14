from evaluator import *

firstdata = get_data()
G, Dt = firstdata[0], firstdata[1]

obj_prop_old = firstdata[2:]


def force():
        
        global obj_prop_old
        forces = [] 
        for i in obj_prop_old:
            forcesx = []
            forcesy = []
            for j in obj_prop_old:
                if i == j:
                   continue
                else:
                  m1,x1,y1 = i[0:3]
                  m2,x2,y2 = j[0:3]
                  F = float(G*m1*m2)/((x2-x1)**2 + (y2-y1)**2)
                  Fx = float(F*(x2-x1))/((y2-y1)**2 + (x2-x1)**2)**(0.5)
                  Fy = float(F*(y2-y1))/((y2-y1)**2 + (x2-x1)**2)**(0.5)
                  forcesx.append(Fx)
                  forcesy.append(Fy)
            forces.append([sum(forcesx),sum(forcesy)])   
        return forces         
            
def new_velocity():

      global obj_prop_old

      velocity = []
      for i in range(len(obj_prop_old)):
        vx = obj_prop_old[i][3] 
        vy = obj_prop_old[i][4]
        fx = force()[i][0]
        fy = force()[i][1]
        m1 = obj_prop_old[i][0]
        velocity.append([vx+float(Dt*fx)/m1,vy+float(Dt*fy)/m1])
        
      return velocity
      
def new_move():
    
    global obj_prop_old

    list1 = new_velocity()
     
    positions = []
    for i in range(len(obj_prop_old)):
      new_position = [obj_prop_old[i][1] + obj_prop_old[i][3]*Dt,obj_prop_old[i][2] + obj_prop_old[i][4]*Dt]
      positions.append(new_position)
    
    delta_pos =[]
    for i in range(len(obj_prop_old)):
      n_delta_pos = [obj_prop_old[i][3]*Dt,obj_prop_old[i][4]*Dt]
      delta_pos.append(n_delta_pos)
    
    masses = []
    for i in range(len(obj_prop_old)):
      masses.append([obj_prop_old[i][0]])
    
    obj_prop_old = []
    for i in range(len(masses)):
      obj_prop_old.append(masses[i]+positions[i]+list1[i])  

    return delta_pos     


    
    
      

    
    
    

    


                    

                  
            
        
        





 



