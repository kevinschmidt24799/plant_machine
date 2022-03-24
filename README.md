# plant_machine
This program renders a random tree using openGL, which can be navigated by mouse panning, around and zoomed into and out of using +/-. The program randomly generates many points inside of a hemisphere, as well as a single root on the ground. Then, using Kruskal's algorithm, a minimum spanning tree is produced. Then, little sphere "leaves" are drawn on the leaf nodes, then all nodes are connected with branches with thickness determined by how many children they have, coming in the direction of the root. Finally, these shapes are drawn using openGL. A video demo can be found here: https://youtu.be/5XrREii9RGg


<img src="Tree%20Demo%20Image.png" alt="drawing" width="1000"/>
