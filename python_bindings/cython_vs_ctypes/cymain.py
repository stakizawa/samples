import cUpdate

updater = cUpdate.Updater()

print 'version: %s' % (updater.version())

lst = [1, 2, 3, 4, 5]
print 'test1'
updater.print_values(lst)
updater.update(lst)
updater.print_values(lst)

lst2 = [1, 2, 3, 4, 5]
print 'test2'
updater.print_values(lst2)
updater.update(lst2, updater.increment_one)
updater.print_values(lst2)

lst3 = [1, 2, 3, 4, 5]
print 'test3'
updater.print_values(lst3)
updater.update(lst3, updater.increment_byself)
updater.print_values(lst3)

lst4 = [1, 2, 3, 4, 5]
print 'test4'
updater.print_values(lst4)
updater.update(lst4, updater.decrement_one)
updater.print_values(lst4)
