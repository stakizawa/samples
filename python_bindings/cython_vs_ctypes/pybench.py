import update
import cProfile

N   = 5000000

updater = update.Updater()

lst = []
for i in range(N):
    lst.append(1)

cProfile.run('updater.update(lst, updater.increment_one)')
