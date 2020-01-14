# -*- coding: utf-8 -*-



cp_source = []
cp_source_path = []

last_direct = '/'
last_direct_current = []
last_direct_current2 = []
current_command = ''

current = []
current_path = []

current_others = []
current_path_others = []

def check_commands(FS, C):
  
  global current,current_path,current_others,current_path_others,current_command,last_direct,last_direct_current,last_direct_current2,cp_source,cp_source_path
  
  current = FS
  current_others = FS
  cp_source = FS
  current_path = []
  current_path_others = []
  cp_source_path = []

  last_direct = '/'
  last_direct_current = []
  last_direct_current2 = []
  current_command = ''

  


  
  def cd(path):
   
    global current,current_path,last_direct,last_direct_current,last_direct_current2

    
    
    if path == '':
      current = FS
      current_path = []
    
#absolut path
    elif path[0]== '/':
      current = FS
      current_path = []
      path_without_blanks = filter(None, path.split('/'))

      for i in path_without_blanks:
        if i == '.' or i == ' ':
          continue
        elif i == '..':
          if current_path == []:
            return False
          elif len(current_path) == 1:
            current = FS
            current_path = []
          else:
            current = FS
            for i in current_path[:-1]:
              current = current[i]
            current_path = current_path[:-1]
        else:
          #path control + /the3.py/../the4 
          for m in current:
            if m[0] == i and m[1] in ("d","D"):
              current_path.append(current.index(m))
              current = m
              break
          else:
            return False
      
      #last_direct
      last_direct = path

#relative path
    else:
      path_without_blanks = filter(None, path.split('/'))
    
      for i in path_without_blanks:
        if i == '.' or i == ' ':
          continue
        elif i == '..':
         
          if current_path == []:
            return False
          elif len(current_path) == 1:
            current = FS
            current_path = []
          else:
            current = FS
            for i in current_path[:-1]:
              current = current[i]
            current_path = current_path[:-1]
        else:
          #path control + /the3.py/../the4
          for m in current:
            if m[0] == i and m[1] in ("d","D"):
              current_path.append(current.index(m))
              current = m
              break
          else:
            return False
    
    #last_direct
    last_direct = '/'
    last_direct_current2 = []
    last_direct_current = FS[:]
    # rootta ise
    if current_path == []:
      last_direct = '/'
    else:
      for i in current_path:
        last_direct_current2.append(last_direct_current[i][0])
        last_direct_current = last_direct_current[i]
      last_direct+= "/".join(last_direct_current2)

    
  
  
  
  def mkdir(path):
    global current_others,current_path_others
    
    
    current_others = current
    current_path_others = current_path[:]
    
    #cases
    if filter(None, path.split('/')) == [".."]:
      return False
    elif path == '/':
      return False
    elif filter(None, path.split('/')) == ["."]:
      return False
    # mkdir path/..
    elif filter(None, path.split('/'))[-1] == "..":
      return False

    #absolut
    elif path[0] == '/':
      current_others = FS
      current_path_others = []
      
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))

        
      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
     
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False
  
    #relative
    else:
      
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))
      
      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
         
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    
    #aynı dosyadan var mı kontrolü (sadece dir için sınırlamadık öyle bir isme sahip file varsa da error vermeli)
    for i in current_others:
      if i[0] == path_without_blanks[-1]:
        return False

    
    current_others.append([path_without_blanks[-1],'D'])
      
    
    

  def rmdir(path):
    
    global current_others,current_path_others
    

    current_others = current

    current_path_others = current_path[:]
    
    #cases
    if filter(None, path.split('/')) == [".."]:
      return False
    elif path == "/":
      return False
    elif filter(None, path.split('/')) == ["."]:
      return False
    # rmdir path/..
    elif filter(None, path.split('/'))[-1] == "..":
      return False

    #absolut
    elif path[0] == '/':
      current_others = FS
      current_path_others = []
    
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))

      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
      
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    #relative
    else:
      
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))

      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
    
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    

    for i in current_others:
      if (i[0] == path_without_blanks[-1] and i[1] in ('d','D')) and len(i)==2 and current_path != current_path_others + [current_others.index(i)]:
        current_others.remove(i)
        break
    else:
      return False

    
    

    

  def rm(path):

    global current_others,current_path_others
    

    current_others = current

    current_path_others = current_path[:]

    #cases
    if filter(None, path.split('/')) == [".."]:
      return False
    elif path == '/':
      return False
    elif filter(None, path.split('/')) == ["."]:
      return False
    # rm path/..
    elif filter(None, path.split('/'))[-1] == "..":
      return False
    
    
    #absolut
    elif path[0] == '/':
      current_others = FS
      current_path_others = []
    
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))

      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':

            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4 
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    #relative
    else:
      
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))
      
      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
  
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4 
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    
    for i in current_others:
      if i[0] == path_without_blanks[-1] and i[1] in ('f','F'):
        current_others.remove(i)
        break
    else:
      return False



    

  def cp(source,target):
    global current_others,current_path_others,cp_source,cp_source_path
    
    #her çağrıldığında ilk olarak cd'nin pathine set ediyoruz
    current_others = current
    cp_source = current
    #aliasingi çözmek için shallow copy yapıyoruz (yoksa current_path de değişiyor)
    current_path_others = current_path[:]
    cp_source_path = current_path[:]
    
    #cases
    
    #SOURCE
    #absolut
    if source[0] == '/':
      cp_source = FS
      cp_source_path = []
    
      #path/.
      if filter(None, source.split('/'))[-1] == ".":
        source_without_blanks = filter(None, source.split('/'))[:-1]
      #path/..
      elif filter(None, source.split('/'))[-1] == "..":
        source_without_blanks = filter(None, source.split('/'))[:-2]
      else:
        source_without_blanks = filter(None, source.split('/'))

      for i in source_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
            #rootun üstüne çıkmak istiyor
            if cp_source_path == []:
              return False
            elif len(cp_source_path) == 1:
              cp_source = FS
              cp_source_path = []
            else:
              cp_source = FS
              for i in cp_source_path[:-1]:
                cp_source = cp_source[i]
              cp_source_path = cp_source_path[:-1]
          else:
            #path control + /the3.py/../the4 olayı
            for m in cp_source:
              if m[0] == i and m[1] in ("d","D"):
                cp_source_path.append(cp_source.index(m))
                cp_source = m
                break
            else:
              return False
  
    #relative
    else:
      
      #path/.
      if filter(None, source.split('/'))[-1] == ".":
        source_without_blanks = filter(None, source.split('/'))[:-1]
      #path/..
      elif filter(None, source.split('/'))[-1] == "..":
        source_without_blanks = filter(None, source.split('/'))[:-2]
      else:
        source_without_blanks = filter(None, source.split('/'))


      for i in source_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
            #rootun üstüne çıkmak istiyor
            if cp_source_path == []:
              return False
            elif len(cp_source_path) == 1:
              cp_source = FS
              cp_source_path = []
            else:
              cp_source = FS
              for i in cp_source_path[:-1]:
                cp_source = cp_source[i]
              cp_source_path = cp_source_path[:-1]
          else:
            #path control + /the3.py/../the4 olayı
            for m in cp_source:
              if m[0] == i and m[1] in ("d","D"):
                cp_source_path.append(cp_source.index(m))
                cp_source = m
                break
            else:
              return False



    #TARGETTTT
    #absolut
    if target[0] == '/':
      current_others = FS
      current_path_others = []
    
      #path/.
      if filter(None, target.split('/'))[-1] == ".":
        target_without_blanks = filter(None, target.split('/'))[:-1]
      #path/..
      elif filter(None, target.split('/'))[-1] == "..":
        target_without_blanks = filter(None, target.split('/'))[:-2]
      else:
        target_without_blanks = filter(None, target.split('/'))

      for i in target_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
            #rootun üstüne çıkmak istiyor
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4 olayı
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False
  
    #relative
    else:
      
      #path/.
      if filter(None, target.split('/'))[-1] == ".":
        target_without_blanks = filter(None, target.split('/'))[:-1]
      #path/..
      elif filter(None, target.split('/'))[-1] == "..":
        target_without_blanks = filter(None, target.split('/'))[:-2]
      else:
        target_without_blanks = filter(None, target.split('/'))

      for i in target_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
            #rootun üstüne çıkmak istiyor
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4 olayı
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    

    #aynı dosyadan var mı kontrolü (sadece dir için sınırlamadık öyle bir isme sahip file varsa da error vermeli)
    for i in cp_source:
      # source file ise
      if i[0] == source_without_blanks[-1] and i[1] in ('f','F'):
        for m in current_others:
          # target file ve var ise 
          if m[0] == target_without_blanks[-1] and m[1] in ('f','F'):
            return False
          elif m[0] == target_without_blanks[-1] and m[1] in ('d','D'):
            for sub in m:
              # sourceun adında bir şey varsa m in altında
              if sub[0] == source_without_blanks[-1]:
                return False
            else:
              #aliasing
              new = i[:]
              m.append(new)
            break
        # target file exist değilse (file1 i file 2 olarak copy et)
        else:
          current_others.append([target_without_blanks[-1],'f'])

        break

      # source folder ise
      elif i[0] == source_without_blanks[-1] and i[1] in ('d','D'):
        for m in current_others:
          #siblinglerde aynı isimde hem dir hem file olamaz file varsa kesin hata
          if m[0] == target_without_blanks[-1] and m[1] in ('f','F'):
            return False
          #folder varsa sourceu onun içine append et
          elif m[0] == target_without_blanks[-1] and m[1] in ('d','D'):
            for sub in m:
              # sourceun adında bir şey varsa m in altında
              if sub[0] == source_without_blanks[-1]:
                return False
            else:
              #aliasing engelleme
              new = i[:]
              m.append(new)
            break
        #folder yoksa folderın ismini target yap at
        else:
          #aliasing engelleme
          new = i[:]
          new[0] = target_without_blanks[-1]
          current_others.append(new)

        break

    #source bulunamadıysa
    else:
      return False

        

  def exec1(path):
    global current_others,current_path_others
    
    #her çağrıldığında ilk olarak cd'nin pathine set ediyoruz
    current_others = current
    #aliasingi çözmek için shallow copy yapıyoruz (yoksa current_path de değişiyor)
    current_path_others = current_path[:]

    #cases
    if filter(None, path.split('/')) == [".."]:
      return False
    elif path == '/':
      return False
    elif filter(None, path.split('/')) == ["."]:
      return False
    # exec path/..
    elif filter(None, path.split('/'))[-1] == "..":
      return False
    

    #absolut
    elif path[0] == '/':
      current_others = FS
      current_path_others = []
    
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))

      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
            #rootun üstüne çıkmak istiyor
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4 olayı
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    #relative
    else:
      
      #path/.
      if filter(None, path.split('/'))[-1] == ".":
        path_without_blanks = filter(None, path.split('/'))[:-1]
      else:
        path_without_blanks = filter(None, path.split('/'))

      for i in path_without_blanks[:-1]:
          if i == '.' :
            continue
          elif i == '..':
            #rootun üstüne çıkmak istiyor
            if current_path_others == []:
              return False
            elif len(current_path_others) == 1:
              current_others = FS
              current_path_others = []
            else:
              current_others = FS
              for i in current_path_others[:-1]:
                current_others = current_others[i]
              current_path_others = current_path_others[:-1]
          else:
            #path control + /the3.py/../the4 olayı
            for m in current_others:
              if m[0] == i and m[1] in ("d","D"):
                current_path_others.append(current_others.index(m))
                current_others = m
                break
            else:
              return False

    
    #aynı dosyadan var mı kontrolü 
    for i in current_others:
      if i[0] == path_without_blanks[-1] and i[1] in ('f','F'):
        break
    else:
      return False
    
  
  
  #Getting parameters
  for i in C:
    current_command = i
    splitted_par = i.split(' ')
    first_two = splitted_par[0]
    #cd de vs '' olayı için
    if len(splitted_par) == 1:
      last = ''
    else:
      last = splitted_par[1]
    
    if first_two == 'cd':
      # cd '' olayı için uzunluk 1 de olabilir
      if len(splitted_par) > 2:
        return('ERROR', current_command, last_direct)
      else:
        #hata veriyorsa
        if cd(last) == False:
          return('ERROR', current_command, last_direct)
        
    elif first_two == 'mkdir':
      if len(splitted_par) == 2:
        if mkdir(last) == False:
          return('ERROR', current_command, last_direct)
      else:
        return('ERROR', current_command, last_direct)

    elif first_two == 'rmdir':
      if len(splitted_par) == 2:
        if rmdir(last) == False:
          return('ERROR', current_command, last_direct)
      else:
        return('ERROR', current_command, last_direct)

    elif first_two == 'rm':
      if len(splitted_par) == 2:
        if rm(last) == False:
          return('ERROR', current_command, last_direct)
      else:
        return('ERROR', current_command, last_direct)

    elif first_two == 'cp':
      if len(splitted_par) == 3:
        if cp(splitted_par[1],splitted_par[2]) == False:
          return('ERROR', current_command, last_direct)
      else:
        return('ERROR', current_command, last_direct)

    elif first_two == 'exec':
      if len(splitted_par) == 2:
        if exec1(last) == False:
          return('ERROR', current_command, last_direct)
      else:
        return('ERROR', current_command, last_direct)
    #verilen komut hiçbir şeye karşılık gelmiyorsa
    else:
      return('ERROR', current_command, last_direct)

  return ("SUCCESS", FS, last_direct)



FS = ["/", "d",
["home", "D", ["the4", "d", ["the4", "D"], ["the.py", "F"]]],
["etc", "d"],
["tmp", "D", ["tmp.sh", "f"], ["del.txt", "F"]]
]

C1 = ["mkdir /home/the5/."]

print check_commands(FS, C1)
print current_others
print FS
print current
print current_path_others 
print current_path
