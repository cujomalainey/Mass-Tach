# Use this script to benchmark the database and fill it with dummy content
import pymysql.cursors

import time
import random

# Connect to the database
connection = pymysql.connect(host='localhost',
                             user='root',
                             db='mass_tach')

try:
    with connection.cursor() as cursor:
        # Create a new record
        sql = "INSERT INTO `events` (`name`, `start`, `end`, `owner_id`) VALUES ({}, '{}', '{}', 1)"\
            .format("'temp'", time.strftime('%Y-%m-%d %H:%M:%S'), time.strftime('%Y-%m-%d %H:%M:%S'))
        cursor.execute(sql)

    # connection is not autocommit by default. So you must commit to save
    # your changes.
    connection.commit()

    for i in range(0, 100):
        with connection.cursor() as cursor:
            # Create a new record
            sql = "INSERT INTO `teams` (`name`, `bike_id`, `event_id`) VALUES ('{}', {}, 1)"\
                .format("team{}".format(i), i)
            cursor.execute(sql)
    connection.commit()

    t = time.time()
    for i in range(0, 2880):
        temp_time = t + 60*i
        for team in range(0, 100):
            with connection.cursor() as cursor:
                # Read a single record
                sql = "INSERT INTO `pings` (`submission_time`, `count`, `device_id`) VALUES ('{}', {}, {})"\
                    .format(
                        time.strftime(
                            '%Y-%m-%d %H:%M:%S',
                            time.localtime(
                                temp_time + random.randint(0, 59))), random.randint(30, 150), team)
                cursor.execute(sql)
        connection.commit()
finally:
    connection.close()
