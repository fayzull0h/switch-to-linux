from urllib.request import Request, urlopen
import ssl
import json
import sys
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

urlbase = "https://cdn.jsdelivr.net/gh/fawazahmed0/quran-api@1/editions/eng-mustafakhattaba/"

def print_verse(chapter, verse):
    vnum = 0
    chapterinfo = []
    while True:
        try:
            intchapter = int(chapter)
            if (intchapter < 1 or intchapter > 114):
                raise Exception("Invalid chapter")
        
            chapterurl = urlbase + chapter + ".json"
            rawchapter = urlopen(chapterurl,context=ctx)
            chapterinfo = json.loads(rawchapter.read().decode())
            vnum = len(chapterinfo["chapter"])
        except:
            chapter = input("Re-enter chapter (1-114): ")

        try:
            intverse = int(verse)
            if (intverse < 1 or intverse > vnum):
                raise Exception("Invalid verse")

            print(intverse, "-->", chapterinfo["chapter"][intverse - 1]["text"])
            command = input("")
            if command == 'n':
                if intverse == vnum:
                    break
                verse = str(intverse + 1)
            elif command == 'b':
                if intverse == 1:
                    break
                verse = str(intverse - 1)
            else:
                break
        except Exception as err:
            verse = input("Re-enter verse (1-" + str(vnum) + ": ")

def no_info():
    chapter = input("Which chapter? ")
    verse = input("Which verse? ")

    print_verse(chapter, verse)

def given_chapter():
    chapter = sys.argv[1]
    verse = input("Which verse would you like to see?: ")
    
    print_verse(chapter, verse)

def given_both():
    chapter = sys.argv[1]
    verse = sys.argv[2]

    if verse == "--all":
        try:
            intchapter = int(chapter)
            if (intchapter < 1 or intchapter > 114):
                raise Exception("Invalid chapter")
        except:
            chapter = input("Re-enter chapter (1-114): ")

        chapterurl = urlbase + chapter + ".json"
        rawchapter = urlopen(chapterurl, context=ctx)
        chapterinfo = json.loads(rawchapter.read().decode())
        for i in range(len(chapterinfo["chapter"])):
            print(i+1,"-->", chapterinfo["chapter"][i]["text"])
        return

    print_verse(chapter, verse)

if len(sys.argv) == 1:
    no_info()
elif len(sys.argv) == 2:
    given_chapter()
else:
    given_both()

