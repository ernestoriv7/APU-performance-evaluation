# 1000 objetos,  resolucion 1280x720
sed '5 c xresolution&1280' 1000.sc > cpu/1000CPU000-1280x720.sc
sed -i '6c yresolution&720' cpu/1000CPU000-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU000-1280x720.sc > gpu/1000GPU000-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU000-1280x720.sc > apu/1000APU000-1280x720.sc 

sed '3 c reflections&5' cpu/1000CPU000-1280x720.sc > cpu/1000CPU001-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU001-1280x720.sc > gpu/1000GPU001-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU001-1280x720.sc > apu/1000APU001-1280x720.sc 

sed '2 c transparencies&5' cpu/1000CPU000-1280x720.sc > cpu/1000CPU010-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU010-1280x720.sc > gpu/1000GPU010-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU010-1280x720.sc > apu/1000APU010-1280x720.sc 

sed '3 c reflections&5' cpu/1000CPU010-1280x720.sc > cpu/1000CPU011-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU011-1280x720.sc > gpu/1000GPU011-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU011-1280x720.sc > apu/1000APU011-1280x720.sc 

sed '1 c antialiasing&ON' cpu/1000CPU000-1280x720.sc > cpu/1000CPU100-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU100-1280x720.sc > gpu/1000GPU100-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU100-1280x720.sc > apu/1000APU100-1280x720.sc 

sed '3 c reflections&5' cpu/1000CPU100-1280x720.sc > cpu/1000CPU101-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU101-1280x720.sc > gpu/1000GPU101-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU101-1280x720.sc > apu/1000APU101-1280x720.sc 

sed '2 c transparencies&5' cpu/1000CPU100-1280x720.sc > cpu/1000CPU110-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU110-1280x720.sc > gpu/1000GPU110-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU110-1280x720.sc > apu/1000APU110-1280x720.sc 

sed '3 c reflections&5' cpu/1000CPU110-1280x720.sc > cpu/1000CPU111-1280x720.sc
sed '4 c architecture&GPU' cpu/1000CPU111-1280x720.sc > gpu/1000GPU111-1280x720.sc
sed '4 c architecture&APU' cpu/1000CPU111-1280x720.sc > apu/1000APU111-1280x720.sc 

# 1000 objetos,  resolucion 1440x900
sed '5 c xresolution&1440' 1000.sc > cpu/1000CPU000-1440x900.sc
sed -i '6c yresolution&900' cpu/1000CPU000-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU000-1440x900.sc > gpu/1000GPU000-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU000-1440x900.sc > apu/1000APU000-1440x900.sc 

sed '3 c reflections&5' cpu/1000CPU000-1440x900.sc > cpu/1000CPU001-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU001-1440x900.sc > gpu/1000GPU001-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU001-1440x900.sc > apu/1000APU001-1440x900.sc 

sed '2 c transparencies&5' cpu/1000CPU000-1440x900.sc > cpu/1000CPU010-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU010-1440x900.sc > gpu/1000GPU010-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU010-1440x900.sc > apu/1000APU010-1440x900.sc 

sed '3 c reflections&5' cpu/1000CPU010-1440x900.sc > cpu/1000CPU011-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU011-1440x900.sc > gpu/1000GPU011-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU011-1440x900.sc > apu/1000APU011-1440x900.sc 

sed '1 c antialiasing&ON' cpu/1000CPU000-1440x900.sc > cpu/1000CPU100-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU100-1440x900.sc > gpu/1000GPU100-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU100-1440x900.sc > apu/1000APU100-1440x900.sc 

sed '3 c reflections&5' cpu/1000CPU100-1440x900.sc > cpu/1000CPU101-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU101-1440x900.sc > gpu/1000GPU101-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU101-1440x900.sc > apu/1000APU101-1440x900.sc 

sed '2 c transparencies&5' cpu/1000CPU100-1440x900.sc > cpu/1000CPU110-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU110-1440x900.sc > gpu/1000GPU110-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU110-1440x900.sc > apu/1000APU110-1440x900.sc 

sed '3 c reflections&5' cpu/1000CPU110-1440x900.sc > cpu/1000CPU111-1440x900.sc
sed '4 c architecture&GPU' cpu/1000CPU111-1440x900.sc > gpu/1000GPU111-1440x900.sc
sed '4 c architecture&APU' cpu/1000CPU111-1440x900.sc > apu/1000APU111-1440x900.sc 

# 1000 objetos,  resolucion 1920x1080
sed '5 c xresolution&1920' 1000.sc > cpu/1000CPU000-1920x1080.sc
sed -i '6c yresolution&1080' cpu/1000CPU000-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU000-1920x1080.sc > gpu/1000GPU000-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU000-1920x1080.sc > apu/1000APU000-1920x1080.sc 

sed '3 c reflections&5' cpu/1000CPU000-1920x1080.sc > cpu/1000CPU001-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU001-1920x1080.sc > gpu/1000GPU001-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU001-1920x1080.sc > apu/1000APU001-1920x1080.sc 

sed '2 c transparencies&5' cpu/1000CPU000-1920x1080.sc > cpu/1000CPU010-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU010-1920x1080.sc > gpu/1000GPU010-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU010-1920x1080.sc > apu/1000APU010-1920x1080.sc 

sed '3 c reflections&5' cpu/1000CPU010-1920x1080.sc > cpu/1000CPU011-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU011-1920x1080.sc > gpu/1000GPU011-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU011-1920x1080.sc > apu/1000APU011-1920x1080.sc 

sed '1 c antialiasing&ON' cpu/1000CPU000-1920x1080.sc > cpu/1000CPU100-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU100-1920x1080.sc > gpu/1000GPU100-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU100-1920x1080.sc > apu/1000APU100-1920x1080.sc 

sed '3 c reflections&5' cpu/1000CPU100-1920x1080.sc > cpu/1000CPU101-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU101-1920x1080.sc > gpu/1000GPU101-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU101-1920x1080.sc > apu/1000APU101-1920x1080.sc 

sed '2 c transparencies&5' cpu/1000CPU100-1920x1080.sc > cpu/1000CPU110-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU110-1920x1080.sc > gpu/1000GPU110-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU110-1920x1080.sc > apu/1000APU110-1920x1080.sc 

sed '3 c reflections&5' cpu/1000CPU110-1920x1080.sc > cpu/1000CPU111-1920x1080.sc
sed '4 c architecture&GPU' cpu/1000CPU111-1920x1080.sc > gpu/1000GPU111-1920x1080.sc
sed '4 c architecture&APU' cpu/1000CPU111-1920x1080.sc > apu/1000APU111-1920x1080.sc 


# 4000 objetos,  resolucion 1280x720
sed '5 c xresolution&1280' 4000.sc > cpu/4000CPU000-1280x720.sc
sed -i '6c yresolution&720' cpu/4000CPU000-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU000-1280x720.sc > gpu/4000GPU000-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU000-1280x720.sc > apu/4000APU000-1280x720.sc 

sed '3 c reflections&5' cpu/4000CPU000-1280x720.sc > cpu/4000CPU001-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU001-1280x720.sc > gpu/4000GPU001-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU001-1280x720.sc > apu/4000APU001-1280x720.sc 

sed '2 c transparencies&5' cpu/4000CPU000-1280x720.sc > cpu/4000CPU010-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU010-1280x720.sc > gpu/4000GPU010-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU010-1280x720.sc > apu/4000APU010-1280x720.sc 

sed '3 c reflections&5' cpu/4000CPU010-1280x720.sc > cpu/4000CPU011-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU011-1280x720.sc > gpu/4000GPU011-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU011-1280x720.sc > apu/4000APU011-1280x720.sc 

sed '1 c antialiasing&ON' cpu/4000CPU000-1280x720.sc > cpu/4000CPU100-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU100-1280x720.sc > gpu/4000GPU100-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU100-1280x720.sc > apu/4000APU100-1280x720.sc 

sed '3 c reflections&5' cpu/4000CPU100-1280x720.sc > cpu/4000CPU101-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU101-1280x720.sc > gpu/4000GPU101-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU101-1280x720.sc > apu/4000APU101-1280x720.sc 

sed '2 c transparencies&5' cpu/4000CPU100-1280x720.sc > cpu/4000CPU110-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU110-1280x720.sc > gpu/4000GPU110-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU110-1280x720.sc > apu/4000APU110-1280x720.sc 

sed '3 c reflections&5' cpu/4000CPU110-1280x720.sc > cpu/4000CPU111-1280x720.sc
sed '4 c architecture&GPU' cpu/4000CPU111-1280x720.sc > gpu/4000GPU111-1280x720.sc
sed '4 c architecture&APU' cpu/4000CPU111-1280x720.sc > apu/4000APU111-1280x720.sc 

# 4000 objetos,  resolucion 1440x900
sed '5 c xresolution&1440' 4000.sc > cpu/4000CPU000-1440x900.sc
sed -i '6c yresolution&900' cpu/4000CPU000-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU000-1440x900.sc > gpu/4000GPU000-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU000-1440x900.sc > apu/4000APU000-1440x900.sc 

sed '3 c reflections&5' cpu/4000CPU000-1440x900.sc > cpu/4000CPU001-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU001-1440x900.sc > gpu/4000GPU001-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU001-1440x900.sc > apu/4000APU001-1440x900.sc 

sed '2 c transparencies&5' cpu/4000CPU000-1440x900.sc > cpu/4000CPU010-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU010-1440x900.sc > gpu/4000GPU010-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU010-1440x900.sc > apu/4000APU010-1440x900.sc 

sed '3 c reflections&5' cpu/4000CPU010-1440x900.sc > cpu/4000CPU011-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU011-1440x900.sc > gpu/4000GPU011-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU011-1440x900.sc > apu/4000APU011-1440x900.sc 

sed '1 c antialiasing&ON' cpu/4000CPU000-1440x900.sc > cpu/4000CPU100-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU100-1440x900.sc > gpu/4000GPU100-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU100-1440x900.sc > apu/4000APU100-1440x900.sc 

sed '3 c reflections&5' cpu/4000CPU100-1440x900.sc > cpu/4000CPU101-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU101-1440x900.sc > gpu/4000GPU101-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU101-1440x900.sc > apu/4000APU101-1440x900.sc 

sed '2 c transparencies&5' cpu/4000CPU100-1440x900.sc > cpu/4000CPU110-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU110-1440x900.sc > gpu/4000GPU110-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU110-1440x900.sc > apu/4000APU110-1440x900.sc 

sed '3 c reflections&5' cpu/4000CPU110-1440x900.sc > cpu/4000CPU111-1440x900.sc
sed '4 c architecture&GPU' cpu/4000CPU111-1440x900.sc > gpu/4000GPU111-1440x900.sc
sed '4 c architecture&APU' cpu/4000CPU111-1440x900.sc > apu/4000APU111-1440x900.sc 

# 4000 objetos,  resolucion 1920x1080
sed '5 c xresolution&1920' 4000.sc > cpu/4000CPU000-1920x1080.sc
sed -i '6c yresolution&1080' cpu/4000CPU000-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU000-1920x1080.sc > gpu/4000GPU000-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU000-1920x1080.sc > apu/4000APU000-1920x1080.sc 

sed '3 c reflections&5' cpu/4000CPU000-1920x1080.sc > cpu/4000CPU001-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU001-1920x1080.sc > gpu/4000GPU001-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU001-1920x1080.sc > apu/4000APU001-1920x1080.sc 

sed '2 c transparencies&5' cpu/4000CPU000-1920x1080.sc > cpu/4000CPU010-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU010-1920x1080.sc > gpu/4000GPU010-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU010-1920x1080.sc > apu/4000APU010-1920x1080.sc 

sed '3 c reflections&5' cpu/4000CPU010-1920x1080.sc > cpu/4000CPU011-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU011-1920x1080.sc > gpu/4000GPU011-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU011-1920x1080.sc > apu/4000APU011-1920x1080.sc 

sed '1 c antialiasing&ON' cpu/4000CPU000-1920x1080.sc > cpu/4000CPU100-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU100-1920x1080.sc > gpu/4000GPU100-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU100-1920x1080.sc > apu/4000APU100-1920x1080.sc 

sed '3 c reflections&5' cpu/4000CPU100-1920x1080.sc > cpu/4000CPU101-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU101-1920x1080.sc > gpu/4000GPU101-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU101-1920x1080.sc > apu/4000APU101-1920x1080.sc 

sed '2 c transparencies&5' cpu/4000CPU100-1920x1080.sc > cpu/4000CPU110-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU110-1920x1080.sc > gpu/4000GPU110-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU110-1920x1080.sc > apu/4000APU110-1920x1080.sc 

sed '3 c reflections&5' cpu/4000CPU110-1920x1080.sc > cpu/4000CPU111-1920x1080.sc
sed '4 c architecture&GPU' cpu/4000CPU111-1920x1080.sc > gpu/4000GPU111-1920x1080.sc
sed '4 c architecture&APU' cpu/4000CPU111-1920x1080.sc > apu/4000APU111-1920x1080.sc 

# 16000 objetos,  resolucion 1280x720
sed '5 c xresolution&1280' 16000.sc > cpu/16000CPU000-1280x720.sc
sed -i '6c yresolution&720' cpu/16000CPU000-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU000-1280x720.sc > gpu/16000GPU000-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU000-1280x720.sc > apu/16000APU000-1280x720.sc 

sed '3 c reflections&5' cpu/16000CPU000-1280x720.sc > cpu/16000CPU001-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU001-1280x720.sc > gpu/16000GPU001-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU001-1280x720.sc > apu/16000APU001-1280x720.sc 

sed '2 c transparencies&5' cpu/16000CPU000-1280x720.sc > cpu/16000CPU010-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU010-1280x720.sc > gpu/16000GPU010-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU010-1280x720.sc > apu/16000APU010-1280x720.sc 

sed '3 c reflections&5' cpu/16000CPU010-1280x720.sc > cpu/16000CPU011-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU011-1280x720.sc > gpu/16000GPU011-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU011-1280x720.sc > apu/16000APU011-1280x720.sc 

sed '1 c antialiasing&ON' cpu/16000CPU000-1280x720.sc > cpu/16000CPU100-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU100-1280x720.sc > gpu/16000GPU100-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU100-1280x720.sc > apu/16000APU100-1280x720.sc 

sed '3 c reflections&5' cpu/16000CPU100-1280x720.sc > cpu/16000CPU101-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU101-1280x720.sc > gpu/16000GPU101-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU101-1280x720.sc > apu/16000APU101-1280x720.sc 

sed '2 c transparencies&5' cpu/16000CPU100-1280x720.sc > cpu/16000CPU110-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU110-1280x720.sc > gpu/16000GPU110-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU110-1280x720.sc > apu/16000APU110-1280x720.sc 

sed '3 c reflections&5' cpu/16000CPU110-1280x720.sc > cpu/16000CPU111-1280x720.sc
sed '4 c architecture&GPU' cpu/16000CPU111-1280x720.sc > gpu/16000GPU111-1280x720.sc
sed '4 c architecture&APU' cpu/16000CPU111-1280x720.sc > apu/16000APU111-1280x720.sc 

# 16000 objetos,  resolucion 1440x900
sed '5 c xresolution&1440' 16000.sc > cpu/16000CPU000-1440x900.sc
sed -i '6c yresolution&900' cpu/16000CPU000-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU000-1440x900.sc > gpu/16000GPU000-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU000-1440x900.sc > apu/16000APU000-1440x900.sc 

sed '3 c reflections&5' cpu/16000CPU000-1440x900.sc > cpu/16000CPU001-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU001-1440x900.sc > gpu/16000GPU001-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU001-1440x900.sc > apu/16000APU001-1440x900.sc 

sed '2 c transparencies&5' cpu/16000CPU000-1440x900.sc > cpu/16000CPU010-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU010-1440x900.sc > gpu/16000GPU010-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU010-1440x900.sc > apu/16000APU010-1440x900.sc 

sed '3 c reflections&5' cpu/16000CPU010-1440x900.sc > cpu/16000CPU011-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU011-1440x900.sc > gpu/16000GPU011-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU011-1440x900.sc > apu/16000APU011-1440x900.sc 

sed '1 c antialiasing&ON' cpu/16000CPU000-1440x900.sc > cpu/16000CPU100-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU100-1440x900.sc > gpu/16000GPU100-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU100-1440x900.sc > apu/16000APU100-1440x900.sc 

sed '3 c reflections&5' cpu/16000CPU100-1440x900.sc > cpu/16000CPU101-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU101-1440x900.sc > gpu/16000GPU101-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU101-1440x900.sc > apu/16000APU101-1440x900.sc 

sed '2 c transparencies&5' cpu/16000CPU100-1440x900.sc > cpu/16000CPU110-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU110-1440x900.sc > gpu/16000GPU110-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU110-1440x900.sc > apu/16000APU110-1440x900.sc 

sed '3 c reflections&5' cpu/16000CPU110-1440x900.sc > cpu/16000CPU111-1440x900.sc
sed '4 c architecture&GPU' cpu/16000CPU111-1440x900.sc > gpu/16000GPU111-1440x900.sc
sed '4 c architecture&APU' cpu/16000CPU111-1440x900.sc > apu/16000APU111-1440x900.sc 

# 16000 objetos,  resolucion 1920x1080
sed '5 c xresolution&1920' 16000.sc > cpu/16000CPU000-1920x1080.sc
sed -i '6c yresolution&1080' cpu/16000CPU000-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU000-1920x1080.sc > gpu/16000GPU000-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU000-1920x1080.sc > apu/16000APU000-1920x1080.sc 

sed '3 c reflections&5' cpu/16000CPU000-1920x1080.sc > cpu/16000CPU001-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU001-1920x1080.sc > gpu/16000GPU001-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU001-1920x1080.sc > apu/16000APU001-1920x1080.sc 

sed '2 c transparencies&5' cpu/16000CPU000-1920x1080.sc > cpu/16000CPU010-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU010-1920x1080.sc > gpu/16000GPU010-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU010-1920x1080.sc > apu/16000APU010-1920x1080.sc 

sed '3 c reflections&5' cpu/16000CPU010-1920x1080.sc > cpu/16000CPU011-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU011-1920x1080.sc > gpu/16000GPU011-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU011-1920x1080.sc > apu/16000APU011-1920x1080.sc 

sed '1 c antialiasing&ON' cpu/16000CPU000-1920x1080.sc > cpu/16000CPU100-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU100-1920x1080.sc > gpu/16000GPU100-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU100-1920x1080.sc > apu/16000APU100-1920x1080.sc 

sed '3 c reflections&5' cpu/16000CPU100-1920x1080.sc > cpu/16000CPU101-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU101-1920x1080.sc > gpu/16000GPU101-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU101-1920x1080.sc > apu/16000APU101-1920x1080.sc 

sed '2 c transparencies&5' cpu/16000CPU100-1920x1080.sc > cpu/16000CPU110-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU110-1920x1080.sc > gpu/16000GPU110-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU110-1920x1080.sc > apu/16000APU110-1920x1080.sc 

sed '3 c reflections&5' cpu/16000CPU110-1920x1080.sc > cpu/16000CPU111-1920x1080.sc
sed '4 c architecture&GPU' cpu/16000CPU111-1920x1080.sc > gpu/16000GPU111-1920x1080.sc
sed '4 c architecture&APU' cpu/16000CPU111-1920x1080.sc > apu/16000APU111-1920x1080.sc 

# 65000 objetos,  resolucion 1280x720
sed '5 c xresolution&1280' 65000.sc > cpu/65000CPU000-1280x720.sc
sed -i '6c yresolution&720' cpu/65000CPU000-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU000-1280x720.sc > gpu/65000GPU000-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU000-1280x720.sc > apu/65000APU000-1280x720.sc 

sed '3 c reflections&5' cpu/65000CPU000-1280x720.sc > cpu/65000CPU001-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU001-1280x720.sc > gpu/65000GPU001-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU001-1280x720.sc > apu/65000APU001-1280x720.sc 

sed '2 c transparencies&5' cpu/65000CPU000-1280x720.sc > cpu/65000CPU010-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU010-1280x720.sc > gpu/65000GPU010-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU010-1280x720.sc > apu/65000APU010-1280x720.sc 

sed '3 c reflections&5' cpu/65000CPU010-1280x720.sc > cpu/65000CPU011-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU011-1280x720.sc > gpu/65000GPU011-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU011-1280x720.sc > apu/65000APU011-1280x720.sc 

sed '1 c antialiasing&ON' cpu/65000CPU000-1280x720.sc > cpu/65000CPU100-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU100-1280x720.sc > gpu/65000GPU100-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU100-1280x720.sc > apu/65000APU100-1280x720.sc 

sed '3 c reflections&5' cpu/65000CPU100-1280x720.sc > cpu/65000CPU101-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU101-1280x720.sc > gpu/65000GPU101-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU101-1280x720.sc > apu/65000APU101-1280x720.sc 

sed '2 c transparencies&5' cpu/65000CPU100-1280x720.sc > cpu/65000CPU110-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU110-1280x720.sc > gpu/65000GPU110-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU110-1280x720.sc > apu/65000APU110-1280x720.sc 

sed '3 c reflections&5' cpu/65000CPU110-1280x720.sc > cpu/65000CPU111-1280x720.sc
sed '4 c architecture&GPU' cpu/65000CPU111-1280x720.sc > gpu/65000GPU111-1280x720.sc
sed '4 c architecture&APU' cpu/65000CPU111-1280x720.sc > apu/65000APU111-1280x720.sc 

# 65000 objetos,  resolucion 1440x900
sed '5 c xresolution&1440' 65000.sc > cpu/65000CPU000-1440x900.sc
sed -i '6c yresolution&900' cpu/65000CPU000-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU000-1440x900.sc > gpu/65000GPU000-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU000-1440x900.sc > apu/65000APU000-1440x900.sc 

sed '3 c reflections&5' cpu/65000CPU000-1440x900.sc > cpu/65000CPU001-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU001-1440x900.sc > gpu/65000GPU001-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU001-1440x900.sc > apu/65000APU001-1440x900.sc 

sed '2 c transparencies&5' cpu/65000CPU000-1440x900.sc > cpu/65000CPU010-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU010-1440x900.sc > gpu/65000GPU010-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU010-1440x900.sc > apu/65000APU010-1440x900.sc 

sed '3 c reflections&5' cpu/65000CPU010-1440x900.sc > cpu/65000CPU011-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU011-1440x900.sc > gpu/65000GPU011-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU011-1440x900.sc > apu/65000APU011-1440x900.sc 

sed '1 c antialiasing&ON' cpu/65000CPU000-1440x900.sc > cpu/65000CPU100-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU100-1440x900.sc > gpu/65000GPU100-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU100-1440x900.sc > apu/65000APU100-1440x900.sc 

sed '3 c reflections&5' cpu/65000CPU100-1440x900.sc > cpu/65000CPU101-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU101-1440x900.sc > gpu/65000GPU101-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU101-1440x900.sc > apu/65000APU101-1440x900.sc 

sed '2 c transparencies&5' cpu/65000CPU100-1440x900.sc > cpu/65000CPU110-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU110-1440x900.sc > gpu/65000GPU110-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU110-1440x900.sc > apu/65000APU110-1440x900.sc 

sed '3 c reflections&5' cpu/65000CPU110-1440x900.sc > cpu/65000CPU111-1440x900.sc
sed '4 c architecture&GPU' cpu/65000CPU111-1440x900.sc > gpu/65000GPU111-1440x900.sc
sed '4 c architecture&APU' cpu/65000CPU111-1440x900.sc > apu/65000APU111-1440x900.sc 

# 65000 objetos,  resolucion 1920x1080
sed '5 c xresolution&1920' 65000.sc > cpu/65000CPU000-1920x1080.sc
sed -i '6c yresolution&1080' cpu/65000CPU000-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU000-1920x1080.sc > gpu/65000GPU000-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU000-1920x1080.sc > apu/65000APU000-1920x1080.sc 

sed '3 c reflections&5' cpu/65000CPU000-1920x1080.sc > cpu/65000CPU001-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU001-1920x1080.sc > gpu/65000GPU001-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU001-1920x1080.sc > apu/65000APU001-1920x1080.sc 

sed '2 c transparencies&5' cpu/65000CPU000-1920x1080.sc > cpu/65000CPU010-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU010-1920x1080.sc > gpu/65000GPU010-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU010-1920x1080.sc > apu/65000APU010-1920x1080.sc 

sed '3 c reflections&5' cpu/65000CPU010-1920x1080.sc > cpu/65000CPU011-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU011-1920x1080.sc > gpu/65000GPU011-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU011-1920x1080.sc > apu/65000APU011-1920x1080.sc 

sed '1 c antialiasing&ON' cpu/65000CPU000-1920x1080.sc > cpu/65000CPU100-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU100-1920x1080.sc > gpu/65000GPU100-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU100-1920x1080.sc > apu/65000APU100-1920x1080.sc 

sed '3 c reflections&5' cpu/65000CPU100-1920x1080.sc > cpu/65000CPU101-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU101-1920x1080.sc > gpu/65000GPU101-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU101-1920x1080.sc > apu/65000APU101-1920x1080.sc 

sed '2 c transparencies&5' cpu/65000CPU100-1920x1080.sc > cpu/65000CPU110-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU110-1920x1080.sc > gpu/65000GPU110-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU110-1920x1080.sc > apu/65000APU110-1920x1080.sc 

sed '3 c reflections&5' cpu/65000CPU110-1920x1080.sc > cpu/65000CPU111-1920x1080.sc
sed '4 c architecture&GPU' cpu/65000CPU111-1920x1080.sc > gpu/65000GPU111-1920x1080.sc
sed '4 c architecture&APU' cpu/65000CPU111-1920x1080.sc > apu/65000APU111-1920x1080.sc 

# 260000 objetos,  resolucion 1280x720
sed '5 c xresolution&1280' 260000.sc > cpu/260000CPU000-1280x720.sc
sed -i '6c yresolution&720' cpu/260000CPU000-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU000-1280x720.sc > gpu/260000GPU000-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU000-1280x720.sc > apu/260000APU000-1280x720.sc 

sed '3 c reflections&5' cpu/260000CPU000-1280x720.sc > cpu/260000CPU001-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU001-1280x720.sc > gpu/260000GPU001-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU001-1280x720.sc > apu/260000APU001-1280x720.sc 

sed '2 c transparencies&5' cpu/260000CPU000-1280x720.sc > cpu/260000CPU010-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU010-1280x720.sc > gpu/260000GPU010-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU010-1280x720.sc > apu/260000APU010-1280x720.sc 

sed '3 c reflections&5' cpu/260000CPU010-1280x720.sc > cpu/260000CPU011-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU011-1280x720.sc > gpu/260000GPU011-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU011-1280x720.sc > apu/260000APU011-1280x720.sc 

sed '1 c antialiasing&ON' cpu/260000CPU000-1280x720.sc > cpu/260000CPU100-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU100-1280x720.sc > gpu/260000GPU100-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU100-1280x720.sc > apu/260000APU100-1280x720.sc 

sed '3 c reflections&5' cpu/260000CPU100-1280x720.sc > cpu/260000CPU101-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU101-1280x720.sc > gpu/260000GPU101-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU101-1280x720.sc > apu/260000APU101-1280x720.sc 

sed '2 c transparencies&5' cpu/260000CPU100-1280x720.sc > cpu/260000CPU110-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU110-1280x720.sc > gpu/260000GPU110-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU110-1280x720.sc > apu/260000APU110-1280x720.sc 

sed '3 c reflections&5' cpu/260000CPU110-1280x720.sc > cpu/260000CPU111-1280x720.sc
sed '4 c architecture&GPU' cpu/260000CPU111-1280x720.sc > gpu/260000GPU111-1280x720.sc
sed '4 c architecture&APU' cpu/260000CPU111-1280x720.sc > apu/260000APU111-1280x720.sc 

# 260000 objetos,  resolucion 1440x900
sed '5 c xresolution&1440' 260000.sc > cpu/260000CPU000-1440x900.sc
sed -i '6c yresolution&900' cpu/260000CPU000-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU000-1440x900.sc > gpu/260000GPU000-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU000-1440x900.sc > apu/260000APU000-1440x900.sc 

sed '3 c reflections&5' cpu/260000CPU000-1440x900.sc > cpu/260000CPU001-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU001-1440x900.sc > gpu/260000GPU001-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU001-1440x900.sc > apu/260000APU001-1440x900.sc 

sed '2 c transparencies&5' cpu/260000CPU000-1440x900.sc > cpu/260000CPU010-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU010-1440x900.sc > gpu/260000GPU010-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU010-1440x900.sc > apu/260000APU010-1440x900.sc 

sed '3 c reflections&5' cpu/260000CPU010-1440x900.sc > cpu/260000CPU011-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU011-1440x900.sc > gpu/260000GPU011-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU011-1440x900.sc > apu/260000APU011-1440x900.sc 

sed '1 c antialiasing&ON' cpu/260000CPU000-1440x900.sc > cpu/260000CPU100-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU100-1440x900.sc > gpu/260000GPU100-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU100-1440x900.sc > apu/260000APU100-1440x900.sc 

sed '3 c reflections&5' cpu/260000CPU100-1440x900.sc > cpu/260000CPU101-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU101-1440x900.sc > gpu/260000GPU101-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU101-1440x900.sc > apu/260000APU101-1440x900.sc 

sed '2 c transparencies&5' cpu/260000CPU100-1440x900.sc > cpu/260000CPU110-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU110-1440x900.sc > gpu/260000GPU110-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU110-1440x900.sc > apu/260000APU110-1440x900.sc 

sed '3 c reflections&5' cpu/260000CPU110-1440x900.sc > cpu/260000CPU111-1440x900.sc
sed '4 c architecture&GPU' cpu/260000CPU111-1440x900.sc > gpu/260000GPU111-1440x900.sc
sed '4 c architecture&APU' cpu/260000CPU111-1440x900.sc > apu/260000APU111-1440x900.sc 

# 260000 objetos,  resolucion 1920x1080
sed '5 c xresolution&1920' 260000.sc > cpu/260000CPU000-1920x1080.sc
sed -i '6c yresolution&1080' cpu/260000CPU000-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU000-1920x1080.sc > gpu/260000GPU000-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU000-1920x1080.sc > apu/260000APU000-1920x1080.sc 

sed '3 c reflections&5' cpu/260000CPU000-1920x1080.sc > cpu/260000CPU001-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU001-1920x1080.sc > gpu/260000GPU001-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU001-1920x1080.sc > apu/260000APU001-1920x1080.sc 

sed '2 c transparencies&5' cpu/260000CPU000-1920x1080.sc > cpu/260000CPU010-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU010-1920x1080.sc > gpu/260000GPU010-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU010-1920x1080.sc > apu/260000APU010-1920x1080.sc 

sed '3 c reflections&5' cpu/260000CPU010-1920x1080.sc > cpu/260000CPU011-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU011-1920x1080.sc > gpu/260000GPU011-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU011-1920x1080.sc > apu/260000APU011-1920x1080.sc 

sed '1 c antialiasing&ON' cpu/260000CPU000-1920x1080.sc > cpu/260000CPU100-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU100-1920x1080.sc > gpu/260000GPU100-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU100-1920x1080.sc > apu/260000APU100-1920x1080.sc 

sed '3 c reflections&5' cpu/260000CPU100-1920x1080.sc > cpu/260000CPU101-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU101-1920x1080.sc > gpu/260000GPU101-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU101-1920x1080.sc > apu/260000APU101-1920x1080.sc 

sed '2 c transparencies&5' cpu/260000CPU100-1920x1080.sc > cpu/260000CPU110-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU110-1920x1080.sc > gpu/260000GPU110-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU110-1920x1080.sc > apu/260000APU110-1920x1080.sc 

sed '3 c reflections&5' cpu/260000CPU110-1920x1080.sc > cpu/260000CPU111-1920x1080.sc
sed '4 c architecture&GPU' cpu/260000CPU111-1920x1080.sc > gpu/260000GPU111-1920x1080.sc
sed '4 c architecture&APU' cpu/260000CPU111-1920x1080.sc > apu/260000APU111-1920x1080.sc 

