import numpy as np

n = 3
theta = 0.314
u = np.array( [ [ 1 ], [ 0 ], [ 0 ] ] )
v = np.array( [ [ 0 ], [ 1 ], [ 0 ] ] )

ut = u.transpose()
vt = v.transpose()

R = np.eye( n ) + np.sin( theta )*( v @ ut - u @vt ) + ( np.cos(theta) - 1 )*( u @ ut + v @ vt )

vec = np.array( [ [ 1 ], [ 0 ], [ 0 ] ] )

for i in range( 20 ):
    print( vec, i*theta, np.cos( i*theta ), np.sin( i*theta ) )
    vec = R @ vec
print( vec, 20*theta, np.cos( 20*theta ), np.sin( 20*theta ) )