import pandas as pd, numpy as np, matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


df = pd.read_csv('cones.csv')
yellow_cones = df[df['color']=='yellow']
blue_cones =  df[df['color']=='blue']
print(df['color'].value_counts())

#Plotting on same graph
fig, ax = plt.subplots()               # one figure, one set of axes
ax.scatter(yellow_cones['x'], yellow_cones['y'], c='yellow')
ax.scatter(blue_cones['x'], blue_cones['y'], c='blue')

xsum = 0.0
ysum = 0.0
#Finding geometric center for blue
for x in blue_cones['x']:
    xsum+=x

for y in blue_cones['y']:
    ysum+=y
blue_center = (xsum/len(blue_cones), ysum/len(blue_cones))
xsum = 0.0
ysum = 0.0
#Finding geometric center for yellow
for x in yellow_cones['x']:
    xsum+=x          
for y in yellow_cones['y']:
    ysum+=y
yellow_center = (xsum/len(yellow_cones), ysum/len(yellow_cones))
print("Blue Center: ", blue_center)
print("Yellow Center: ", yellow_center)
ax.plot(blue_center[0], blue_center[1], marker='o', markersize=10, color='blue'
)
ax.plot(yellow_center[0], yellow_center[1], marker='o', markersize=10, color='yellow'
)


# Angular Sorting
blue_cones['Angle'] = np.arctan2(blue_cones['y'] - blue_center[1], blue_cones['x'] - blue_center[0])
yellow_cones['Angle'] = np.arctan2(yellow_cones['y'] - yellow_center[1], yellow_cones['x'] - yellow_center[0])
blue_cones = blue_cones.sort_values(by=['Angle'])
yellow_cones = yellow_cones.sort_values(by=['Angle'])
print(blue_cones)
print(yellow_cones)
num_points = min(len(blue_cones), len(yellow_cones))
cline=np.zeros((num_points+1,2))
for i in range(num_points):
    x_mid = (blue_cones.iloc[i]['x'] + yellow_cones.iloc[i]['x']) / 2
    y_mid = (blue_cones.iloc[i]['y'] + yellow_cones.iloc[i]['y']) / 2
    cline[i] = [x_mid, y_mid]
cline[num_points] = cline[0]  # Closing the loop

#ax.plot(cline[:,0], cline[:,1], color='green')



#Animation
animated_plot,  = ax.plot([], []) #Comma is to extract element from array
print(animated_plot)
t = np.linspace(0, 2, 62) 
def update(frame, ):

    animated_plot.set_data(cline[:frame,0], cline[:frame,1])

    return animated_plot, 
animation = FuncAnimation(fig, update, len(t), interval=25, )
animation.save("centerline.mp4", writer='ffmpeg', fps=40)


plt.axis('equal') # So scale is same
plt.show()
