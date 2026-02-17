import numpy as np
import matplotlib.pyplot as plt
import matplotlib

# matplotlib.use('Agg')

x_data = np.array([
    [289,229],
    [315,270],
    [302,312],
    [274,294],
    [292,351],
    [269,215],
    [306,246],
    [248,209],
    [248,272],
    [249,318],
    [274,232],
    [279,275],
    [254,303],
    [294,321],
    [224,312],
    [348,288],
    [263,304],
    [306,311],
    [286,308],
    [293,301],
    [265,240],
    [240,229],
    [238,240],
    [247,264],
    [219,298],
    [349,213],
    [325,241],
    [299,297],
    [275,353],
    [269,295],
])

y_data = np.array([
    40,
    33,
    32,
    25,
    24,
    36,
    35,
    35,
    26,
    23,
    36,
    29,
    27,
    26,
    22,
    35,
    31,
    28,
    26,
    26,
    34,
    30,
    31,
    29,
    19,
    43,
    37,
    29,
    26,
    25,
])

def calculate_X(x_data, y_data):
    n=y_data.shape[0]
    p=x_data.shape[1]
    X = np.zeros((n, p+1), dtype=float)
    
    for i in range(n):
        X[i, :] = np.array([1] + list(x_data[i]))
    return X

def calculate_theta_hat(x_data, y_data):
    X = calculate_X(x_data, y_data)
    return np.linalg.pinv(X)@y_data

def calculate_y_hat(x, theta):
    x = np.array(x)
    m = x.shape[0]
    y_hat = np.zeros((m,), dtype=float)
    for i in range(m):
        y_hat[i] = theta[0] + np.dot(theta[1:], x[i])
    return y_hat

theta_hat = calculate_theta_hat(x_data, y_data)
print(theta_hat)

predict = lambda x1, x2: calculate_y_hat([[x1, x2]], theta_hat)

@np.vectorize
def calculate_z(x1, x2):
    return predict(x1, x2)[0]


fig = plt.figure()
ax = plt.axes(projection='3d')
y_hat = calculate_y_hat(x_data, theta_hat)

# ax.scatter(x_data[:, 0], x_data[:, 0], y_data)


x = np.linspace(200, 400, 100)
y = np.linspace(200, 400, 100)
X, Y = np.meshgrid(x, y)
Z = calculate_z(X, Y)

ax.plot_surface(X, Y, Z, alpha=0.5)
ax.scatter(x_data[:,0], x_data[:,1], y_data, color="g", alpha=1.0)

ax.set_xlabel("Runs Scored")
ax.set_ylabel("Runs Allowed")
ax.set_zlabel("Wins")

ax.set_xlim([400, 200])
ax.set_ylim([200, 400])

plt.show()
