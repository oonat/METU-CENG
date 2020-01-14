# 
# MODIFY get_data() AS YOU LIKE.
# DO NOT SEND THIS FILE TO US

def get_data():
	"""Get the initial state of the particles & the environment
    * Returns [G, Dt, [m1, x1, y1, vx1, vy1], ...., [mn, xn, yn, vxn, vyn]]"""
      
    #@TODO: Update this function just for your own testing. We will use our own 
    # get_data().
	return [10,1.0,[20.,1000.,400.,0.,0.],[20.,400.,400.,0.,0.],[20.,400.,1000.,0.,0.],[20.,1000.,1000.,0.,0.],[20.,500.,400.,0.,0.],[20.,1000.,200.,0.,0.],[20.,700.,300.,0.,0.]]
