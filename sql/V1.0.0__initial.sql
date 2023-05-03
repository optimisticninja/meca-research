CREATE TABLE entropy (
	rule INTEGER,								-- 32-bit integer of rule
	timestep INTEGER,						-- timestep in evolution
	prev INTEGER,								-- t-1 for second-order
	next INTEGER,								-- t for second order
	type TEXT,									-- description of type of test (random, zeroes, cyclic, half, one, etc.)
	shannon REAL,								-- shannon entropy rating
	timestep_avalanche INTEGER	-- did the bit-avalanche test pass between timesteps?
);
