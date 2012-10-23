#!/usr/bin/python
from subprocess import call
import re

call('cd ~/visayafan.github.com', shell=True)
call('git blame index.html > shan.html', shell=True)
content = open('shan.html', 'r').read()
call('rm -rf shan.html', shell=True)
dateAndLink = re.compile('(\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}):\d{2}.*\<li\>\<a(\shref="(?=Linux|Coding|Algorithm|Compiler|Others|English).*\>)(.+)(\</a\>\</li\>)')
allCont = dateAndLink.findall(content)
allCont.sort()
# for vdate, vlinkpre, vname, vlinkafter in allCont:
#     print vdate, vlinkpre, vname, vlinkafter
htmlcont = open('updates.html').read()
ul = re.compile(r'<ul>')
for vdate, vlinkpre, vname, vlinkafter in allCont:
    if not re.findall(vlinkpre, htmlcont):
        htmlcont = ul.sub('<ul>\n      <li>'+vdate+'&nbsp<a target="_top" '+vlinkpre+vname+vlinkafter, htmlcont)
open('updates.html', 'w').write(htmlcont)
