# -*- coding: utf-8 -*-

"""
  Автор: Кошелева Дарья, группа №P3355

  Решение реализовано внутри функции convert, версия Python: 2.7 
  Конвертация разных типов цифр вынесена в отдельные функции

"""
def convertMonthNumToRu(month):
    result = ''
    if month == 1:
        result = 'января'
    elif month == 2:
        result = 'февраля'
    elif month == 3:
        result = 'марта'
    elif month == 4:
        result = 'апреля'
    elif month == 5:
        result = 'мая'
    elif month == 6:
        result = 'июня'
    elif month == 7:
        result = 'июля'
    elif month == 8:
        result = 'августа'
    elif month == 9:
        result = 'сентября'
    elif month == 10:
        result = 'октября'
    elif month == 11:
        result = 'ноября'
    elif month == 12:
        result = 'декабря'
    #print(result)
    return result

def convertDateLowerDigitToRu(digit, isDay):
    """

    For converting dates in range(0,10) or least significant digit of a number

    """
    result = ''
    if digit == 0 and not isDay:
        result = 'нулевого'
        return result
    if digit == 1:
        result = 'перво'
    elif digit == 2:
        result = 'второ'
    elif digit == 3:
        result = 'треть'
    elif digit == 4:
        result = 'четвёрто'
    elif digit == 5:
        result = 'пято'
    elif digit == 6:
        result = 'шесто'
    elif digit == 7:
        result = 'седьмо'
    elif digit == 8:
        result = 'восьмо'
    elif digit == 9:
        result = 'девято'

    if isDay:
        result += 'е'
    else:
        result += 'го'
    #print(result)
    return result

def convertDateDecadeDigitToRu(digit, isDay):
    """

    For converting dates where mod 10 == 0

    """
    result = ''
    if digit == 1 and isDay:
        result = 'десятое'
    elif digit == 1 and not isDay:
        result = 'десятого'
    elif digit == 2 and isDay:
        result = 'двадцатое'
    elif digit == 2 and not isDay:
        result = 'двадцатого'
    elif digit == 3 and isDay:
        result = 'тридцатое'
    elif digit == 3 and not isDay:
        result = 'тридцатого'
    elif digit == 4:
        result = 'сорокового'
    elif digit == 5:
        result = 'пятидесятого'
    elif digit == 6:
        result = 'шестидесятого'
    elif digit == 7:
        result = 'семидесятого'
    elif digit == 8:
        result = 'восьмидесятого'
    elif digit == 9:
        result = 'девяностого'
    #print(result)
    return result

def convert10To20NumToRu(num, isDay, isTime):
    """

    For converting numbers in range(11,20)

    """
    result = ''
    if num == 11:
        result = 'одиннадцат'
    elif num == 12:
        result = 'двенадцат'
    elif num == 13:
        result = 'тринадцат'
    elif num == 14:
        result = 'четырнадцат'
    elif num == 15:
        result = 'пятадцат'
    elif num == 16:
        result = 'шестнадцат'
    elif num == 17:
        result = 'семнадцат'
    elif num == 18:
        result = 'восемнадцат'
    elif num == 19:
        result = 'девятнадцат'

    if isTime:
        result += 'ь'
    elif isDay:
        result += 'ое'
    else:
        result += 'ого'
    #print(result)
    return result

def convertInfinitiveDecadeDigitToRu(digit, isTime):
    """

    For converting numbers where mod 10 == 0 or decade digit of a number

    """
    result = ''
    if digit == 0:
        return result
    elif digit == 1 and isTime:
        result = 'десять'
    elif digit == 2:
        result = 'двадцать'
    elif digit == 3:
        result = 'тридцать'
    elif digit == 4:
        result = 'сорок'
    elif digit == 5:
        result = 'пятьдесят'
    elif digit == 6:
        result = 'шестьдесят'
    elif digit == 7:
        result = 'семьдесят'
    elif digit == 8:
        result = 'восемьдесят'
    elif digit == 9:
        result = 'девяносто'
    #print(result)
    return result

def convertMillenniumDigitToRu(digit):
    """

    For converting millennium digit in year

    """
    result = ''
    if digit == 0:
        return result
    elif digit == 1:
        result = 'тысяча'
    elif digit == 2:
        result = 'две тысячи'
    #print(result)
    return result

def convertCenturyDigitToRu(digit):
    """

    For converting century digit in year

    """
    result = ''
    if digit == 0:
        return result
    elif digit == 1:
        result = 'сто'
    elif digit == 2:
        result = 'двести'
    elif digit == 3:
        result = 'триста'
    elif digit == 4:
        result = 'четыреста'
    elif digit == 5:
        result = 'пятьсот'
    elif digit == 6:
        result = 'шестьсот'
    elif digit == 7:
        result = 'семьсот'
    elif digit == 8:
        result = 'восемьсот'
    elif digit == 9:
        result = 'девятьсот'
    #print(result)
    return result

def convertTimeDigitToRu(num, isHour):
    """

    For converting lower time digit

    """
    result = ''
    if num == 0:
        result = 'ноль'
    elif num == 1 and isHour:
        result = 'один'
    elif num == 1 and not isHour:
        result = 'одна'
    elif num == 2 and isHour :
        result = 'два'
    elif num == 2 and not isHour:
        result = 'две'
    elif num == 3:
        result = 'три'
    elif num == 4:
        result = 'четыре'
    elif num == 5:
        result = 'пять'
    elif num == 6:
        result = 'шесть'
    elif num == 7:
        result = 'семь'
    elif num == 8:
        result = 'восемь'
    elif num == 9:
        result = 'девять'

    #print(result)
    return result

def convert(dateTimeString):
    result = ''
    error = ''
    datePart = dateTimeString.split(' ')[0]
    timePart = dateTimeString.split(' ')[1]
    #print(datePart)
    #print(timePart)

    """ 
    
    Parsing day, month and year numbers and checking if they are valid (including leap year etc)
    
    """
    dayNumber = int(datePart.split('.')[0])
    if dayNumber not in range(1, 32):
        error += "Wrong day number, it should be in interval [1..31] regarding to month! "
    monthNumber = int(datePart.split('.')[1])
    if monthNumber not in range(1, 13):
        error += "Wrong month number, it should be in interval [1..12]! "
    if monthNumber == 2 and dayNumber > 29:
        error += "Wrong day number for this month, it should be in interval [1..29] regarding to month! "
    if monthNumber not in [1, 3, 5, 7, 8, 10, 12] and dayNumber > 30:
        error += "Wrong day number for this month, it should be in interval [1..30] regarding to month! "
    yearNumber = int(datePart.split('.')[2])
    if yearNumber not in range(0, 2020):
        error += "Wrong year number, it should be in interval [0..2019]! "
    if yearNumber % 4 != 0 and monthNumber == 2 and dayNumber > 28:
        error += "Wrong day number for this month and this year, " \
                 "it should be in interval [1..28] regarding to month and year! "

    #print(dayNumber)
    #print(monthNumber)
    #print(yearNumber)
    """ 

    Parsing hour, minute and second numbers and checking if they are valid

    """
    hourNumber = int(timePart.split(':')[0])
    if hourNumber not in range(0, 24):
        error += "Wrong hour number, it should be in interval [0..23]! "
    minuteNumber = int(timePart.split(':')[1])
    if minuteNumber not in range(0, 60):
        error += "Wrong minute number, it should be in interval [0..59]! "
    secondNumber = int(timePart.split(':')[2])
    if secondNumber not in range(0, 60):
        error += "Wrong second number, it should be in interval [0..59]! "
    #print(hourNumber)
    #print(minuteNumber)
    #print(secondNumber)
    if error != '':
        print(error)
        return error

    """ 

    Adding date to the result

    """
    if dayNumber > 9 and dayNumber % 10 == 0:
        result += convertDateDecadeDigitToRu(dayNumber//10, True)
    elif dayNumber > 19:
        result += convertInfinitiveDecadeDigitToRu(dayNumber//10, False) + ' '
    elif dayNumber in range(11, 20):
        result += convert10To20NumToRu(dayNumber, True, False)

    if dayNumber < 10 or (dayNumber % 10 != 0 and dayNumber not in range(11, 20)):
        result += convertDateLowerDigitToRu((dayNumber+10) % 10, True)

    result += ' ' + convertMonthNumToRu(monthNumber)
    #print(result)

    """ 

    Adding year to the result

    """
    millenniumDigit = yearNumber//1000
    #print(millenniumDigit)
    centuryDigit = yearNumber//100 % 10
    #print(centuryDigit)
    decadeDigit = yearNumber//10 % 10
    #print(decadeDigit)
    lowerYearDigit = yearNumber % 10
    #print(lowerYearDigit)
    twoLowerDigits = yearNumber % 100
    #print(twoLowerDigits)

    millenniumDigitResult = convertMillenniumDigitToRu(millenniumDigit)
    if millenniumDigitResult != '':
        result += ' '
    result += millenniumDigitResult
    #print(result)
    centuryDigitResult = convertCenturyDigitToRu(centuryDigit)
    if centuryDigitResult != '':
        result += ' '
    result += centuryDigitResult
    #print(result)
    decadeDigitResult = ''
    if decadeDigit > 1 and twoLowerDigits % 10 != 0:
        decadeDigitResult = convertInfinitiveDecadeDigitToRu(decadeDigit, False)
    #elif decadeDigit == 1 and lowerYearDigit != 0:
        #decadeDigitResult = convert10To20NumToRu(twoLowerDigits, False, False)
    if decadeDigitResult != '':
        result += ' '
    result += decadeDigitResult
    #print(result)
    lowerYearDigitResult = ''
    if decadeDigit == 1 and lowerYearDigit != 0:
        lowerYearDigitResult = convert10To20NumToRu(twoLowerDigits, False, False)
    elif decadeDigit >= 1 and lowerYearDigit == 0:
        lowerYearDigitResult = convertDateDecadeDigitToRu(decadeDigit, False)
    else:
        lowerYearDigitResult = convertDateLowerDigitToRu(lowerYearDigit, False)
    result += ' ' + lowerYearDigitResult + ' года'
    #print(result)

    """ 

    Adding hours to the result

    """
    if hourNumber < 10:
        result += ' ' + convertTimeDigitToRu(hourNumber, True)
    elif hourNumber in range(11, 20):
        result += ' ' + convert10To20NumToRu(hourNumber, False, True)
    elif hourNumber % 10 == 0:
        result += ' ' + convertInfinitiveDecadeDigitToRu(hourNumber//10, True)
    else:
        result += ' ' + convertInfinitiveDecadeDigitToRu(hourNumber//10, True) + \
                  ' ' + convertTimeDigitToRu(hourNumber % 10, True)
    if hourNumber % 10 == 1 and hourNumber not in range(11, 20):
        result += ' час'
    elif (hourNumber % 10 in [2, 3, 4]) and hourNumber not in range(11, 20):
        result += ' часа'
    else:
        result += ' часов'
    #print(result)
    """ 

    Adding minutes to the result

    """
    if minuteNumber < 10:
        result += ' ' + convertTimeDigitToRu(minuteNumber, False)
    elif minuteNumber in range(11, 20):
        result += ' ' + convert10To20NumToRu(minuteNumber, False, True)
    elif minuteNumber % 10 == 0:
        result += ' ' + convertInfinitiveDecadeDigitToRu(minuteNumber//10, True)
    else:
        result += ' ' + convertInfinitiveDecadeDigitToRu(minuteNumber//10, True) + \
                  ' ' + convertTimeDigitToRu(minuteNumber % 10, False)
    if minuteNumber % 10 == 1 and minuteNumber not in range(11, 20):
        result += ' минута'
    elif (minuteNumber % 10 in [2, 3, 4]) and minuteNumber not in range(11, 20):
        result += ' минуты'
    else:
        result += ' минут'
    #print(result)
    """ 

    Adding seconds to the result

    """
    if secondNumber < 10:
        result += ' ' + convertTimeDigitToRu(secondNumber, False)
    elif secondNumber in range(11, 20):
        result += ' ' + convert10To20NumToRu(secondNumber, False, True)
    elif secondNumber % 10 == 0:
        result += ' ' + convertInfinitiveDecadeDigitToRu(secondNumber//10, True)
    else:
        result += ' ' + convertInfinitiveDecadeDigitToRu(secondNumber//10, True) + \
                  ' ' + convertTimeDigitToRu(secondNumber % 10, False)
    if secondNumber % 10 == 1 and secondNumber not in range(11, 20):
        result += ' секунда'
    elif (secondNumber % 10 in [2, 3, 4]) and secondNumber not in range(11, 20):
        result += ' секунды'
    else:
        result += ' секунд'
    print(result)

    return result

""" 

Checking the result

"""
assert convert('25.09.2019 08:17:59') == \
       "двадцать пятое сентября две тысячи девятнадцатого года восемь часов семнадцать минут пятьдесят девять секунд", \
       'ошибка в тестовом примере 1'

assert convert('10.10.1000 00:20:10') == \
       "десятое октября тысяча нулевого года ноль часов двадцать минут десять секунд", \
       'ошибка в тестовом примере 2'

assert convert('02.05.0999 12:29:00') == \
       "второе мая девятьсот девяносто девятого года двенадцать часов двадцать девять минут ноль секунд", \
       'ошибка в тестовом примере 3'

assert convert('18.01.1120 23:01:04') == \
       "восемнадцатое января тысяча сто двадцатого года двадцать три часа одна минута четыре секунды", \
       'ошибка в тестовом примере 4'

assert convert('20.12.0571 10:45:33') == \
       "двадцатое декабря пятьсот семьдесят первого года десять часов сорок пять минут тридцать три секунды", \
       'ошибка в тестовом примере 5'

assert convert('31.07.1600 01:52:11') == \
       "тридцать первое июля тысяча шестьсот нулевого года один час пятьдесят две минуты одиннадцать секунд", \
       'ошибка в тестовом примере 6'

assert convert('29.02.0021 24:52:11') == \
       "Wrong day number for this month and this year, it should be in interval [1..28] regarding to month and year! " \
       "Wrong hour number, it should be in interval [0..23]! ", \
       'ошибка в тестовом примере 7'

assert convert('28.02.0021 04:00:25') == \
       "двадцать восьмое февраля двадцать первого года четыре часа ноль минут двадцать пять секунд", \
       'ошибка в тестовом примере 8'

assert convert('32.01.2020 04:60:100') == \
       "Wrong day number, it should be in interval [1..31] regarding to month! Wrong year number, " \
       "it should be in interval [0..2019]! Wrong minute number, it should be in interval [0..59]! " \
       "Wrong second number, it should be in interval [0..59]! ", \
       'ошибка в тестовом примере 9'