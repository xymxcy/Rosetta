import os
import csv
import tensorflow as tf
import numpy as np
import pandas as pd
from util import read_dataset

np.set_printoptions(suppress=True)

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

np.random.seed(0)

EPOCHES = 10
BATCH_SIZE = 16
learning_rate = 0.0002

# real data
# ######################################## difference from rosettta
file_x = '../dsets/ALL/cls_train_x.csv'
file_y = '../dsets/ALL/cls_train_y.csv'
real_X, real_Y = pd.read_csv(file_x, header=None).to_numpy(
), pd.read_csv(file_y, header=None).to_numpy()
# ######################################## difference from rosettta
real_X = real_X[:100, :]
real_Y = real_Y[:100, :]
DIM_NUM = real_X.shape[1]

X = tf.placeholder(tf.float64, [None, DIM_NUM])
Y = tf.placeholder(tf.float64, [None, 1])
print(X)
print(Y)

# initialize W & b
W = tf.Variable(tf.zeros([DIM_NUM, 1], dtype=tf.float64))
b = tf.Variable(tf.zeros([1], dtype=tf.float64))
print(W)
print(b)

# predict
pred_Y = tf.sigmoid(tf.matmul(X, W) + b)
print(pred_Y)

# loss
logits = tf.matmul(X, W) + b
loss = tf.nn.sigmoid_cross_entropy_with_logits(labels=Y, logits=logits)
loss = tf.reduce_mean(loss)
print(loss)

# optimizer
train = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss)
print(train)

# save
saver = tf.train.Saver(var_list=None, max_to_keep=5, name='v2')
os.makedirs("./log/ckpt0", exist_ok=True)

init = tf.global_variables_initializer()
print(init)

# restore mpc's model and predict
with tf.Session() as sess:
    sess.run(init)
    if os.path.exists("./log/ckpt0/checkpoint"):
        saver.restore(sess, './log/ckpt0/model')

    # predict
    Y_pred = sess.run(pred_Y, feed_dict={X: real_X, Y: real_Y})
    print("Y_pred:", Y_pred)
