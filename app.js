// ================================================================
// COMPREHENSIVE INDIAN DOMESTIC FLIGHT NETWORK
// 30 cities | 6 airlines | 1500+ flights | Direct + Connecting
// ================================================================

// ===== AIRPORT DATABASE (IATA codes, names, tiers) =====
const AIRPORTS = [
  // Metro / Tier-1
  { city:'Delhi',       iata:'DEL', airport:'Indira Gandhi Intl',              tier:1 },
  { city:'Mumbai',      iata:'BOM', airport:'Chhatrapati Shivaji Maharaj Intl',tier:1 },
  { city:'Bangalore',   iata:'BLR', airport:'Kempegowda Intl',                tier:1 },
  { city:'Chennai',     iata:'MAA', airport:'Chennai Intl',                    tier:1 },
  { city:'Kolkata',     iata:'CCU', airport:'Netaji Subhas Chandra Bose Intl', tier:1 },
  { city:'Hyderabad',   iata:'HYD', airport:'Rajiv Gandhi Intl',              tier:1 },
  // Tier-2
  { city:'Pune',        iata:'PNQ', airport:'Pune Intl',                       tier:2 },
  { city:'Jaipur',      iata:'JAI', airport:'Jaipur Intl',                     tier:2 },
  { city:'Goa',         iata:'GOI', airport:'Dabolim / Manohar Intl',          tier:2 },
  { city:'Ahmedabad',   iata:'AMD', airport:'Sardar Vallabhbhai Patel Intl',   tier:2 },
  { city:'Kochi',       iata:'COK', airport:'Cochin Intl',                     tier:2 },
  { city:'Lucknow',     iata:'LKO', airport:'Chaudhary Charan Singh Intl',     tier:2 },
  { city:'Chandigarh',  iata:'IXC', airport:'Chandigarh Intl',                 tier:2 },
  { city:'Indore',      iata:'IDR', airport:'Devi Ahilyabai Holkar Airport',   tier:2 },
  { city:'Varanasi',    iata:'VNS', airport:'Lal Bahadur Shastri Intl',        tier:2 },
  { city:'Patna',       iata:'PAT', airport:'Jay Prakash Narayan Intl',        tier:2 },
  { city:'Bhubaneswar', iata:'BBI', airport:'Biju Patnaik Intl',               tier:2 },
  { city:'Nagpur',      iata:'NAG', airport:'Dr Babasaheb Ambedkar Intl',      tier:2 },
  // Tier-3
  { city:'Amritsar',    iata:'ATQ', airport:'Sri Guru Ram Dass Jee Intl',      tier:3 },
  { city:'Srinagar',    iata:'SXR', airport:'Sheikh Ul-Alam Intl',             tier:3 },
  { city:'Ranchi',      iata:'IXR', airport:'Birsa Munda Airport',             tier:3 },
  { city:'Raipur',      iata:'RPR', airport:'Swami Vivekananda Airport',       tier:3 },
  { city:'Coimbatore',  iata:'CJB', airport:'Coimbatore Intl',                 tier:3 },
  { city:'Trivandrum',  iata:'TRV', airport:'Trivandrum Intl',                 tier:3 },
  { city:'Mangaluru',   iata:'IXE', airport:'Mangaluru Intl',                  tier:3 },
  { city:'Udaipur',     iata:'UDR', airport:'Maharana Pratap Airport',         tier:3 },
  { city:'Dehradun',    iata:'DED', airport:'Jolly Grant Airport',             tier:3 },
  { city:'Vizag',       iata:'VTZ', airport:'Visakhapatnam Intl',              tier:3 },
  { city:'Madurai',     iata:'IXM', airport:'Madurai Airport',                 tier:3 },
  { city:'Jodhpur',     iata:'JDH', airport:'Jodhpur Airport',                 tier:3 },
];

const CITIES = AIRPORTS.map(a => a.city);
const IATA_MAP = {}; AIRPORTS.forEach(a => { IATA_MAP[a.city] = a.iata; });
function getAirport(city) { return AIRPORTS.find(a => a.city === city); }
function getTier(city) { const a = getAirport(city); return a ? a.tier : 3; }

const AIRLINES = [
  { code:'AI', name:'Air India',  base:4500 },
  { code:'6E', name:'IndiGo',     base:3800 },
  { code:'SG', name:'SpiceJet',   base:3500 },
  { code:'UK', name:'Vistara',    base:5200 },
  { code:'QP', name:'Akasa Air',  base:3900 },
  { code:'G8', name:'GoFirst',    base:3600 },
];

// Route data: multiplier + duration (minutes)
const ROUTE_INFO = {
  'Delhi-Mumbai':[1.0,130],'Delhi-Bangalore':[1.3,165],'Delhi-Chennai':[1.35,170],'Delhi-Kolkata':[1.1,140],
  'Delhi-Hyderabad':[1.15,135],'Delhi-Pune':[1.05,130],'Delhi-Jaipur':[0.7,55],'Delhi-Goa':[1.2,155],
  'Delhi-Ahmedabad':[0.9,100],'Delhi-Kochi':[1.5,190],'Delhi-Lucknow':[0.6,55],'Delhi-Chandigarh':[0.5,50],
  'Delhi-Indore':[0.8,85],'Delhi-Varanasi':[0.65,75],'Delhi-Patna':[0.7,95],'Delhi-Bhubaneswar':[1.05,140],
  'Delhi-Nagpur':[0.85,110],'Delhi-Amritsar':[0.5,55],'Delhi-Srinagar':[0.75,80],'Delhi-Dehradun':[0.45,50],
  'Delhi-Ranchi':[0.85,120],'Delhi-Udaipur':[0.65,75],'Delhi-Jodhpur':[0.6,70],
  'Mumbai-Bangalore':[0.85,100],'Mumbai-Chennai':[1.0,115],'Mumbai-Kolkata':[1.2,155],'Mumbai-Hyderabad':[0.7,80],
  'Mumbai-Pune':[0.4,45],'Mumbai-Jaipur':[0.9,115],'Mumbai-Goa':[0.5,55],'Mumbai-Ahmedabad':[0.5,60],
  'Mumbai-Kochi':[1.1,115],'Mumbai-Lucknow':[1.0,115],'Mumbai-Chandigarh':[1.15,140],'Mumbai-Indore':[0.6,70],
  'Mumbai-Varanasi':[1.05,130],'Mumbai-Nagpur':[0.65,80],'Mumbai-Mangaluru':[0.55,70],'Mumbai-Raipur':[0.75,100],
  'Bangalore-Chennai':[0.5,55],'Bangalore-Kolkata':[1.3,155],'Bangalore-Hyderabad':[0.6,65],
  'Bangalore-Pune':[0.75,85],'Bangalore-Goa':[0.55,55],'Bangalore-Kochi':[0.6,55],'Bangalore-Ahmedabad':[1.1,120],
  'Bangalore-Mangaluru':[0.4,45],'Bangalore-Coimbatore':[0.4,45],'Bangalore-Trivandrum':[0.6,70],
  'Bangalore-Vizag':[0.7,80],'Bangalore-Madurai':[0.45,55],
  'Chennai-Kolkata':[1.2,145],'Chennai-Hyderabad':[0.6,65],'Chennai-Kochi':[0.55,70],
  'Chennai-Coimbatore':[0.4,55],'Chennai-Trivandrum':[0.55,70],'Chennai-Madurai':[0.4,55],'Chennai-Vizag':[0.6,70],
  'Kolkata-Hyderabad':[1.1,130],'Kolkata-Patna':[0.45,55],'Kolkata-Bhubaneswar':[0.45,55],
  'Kolkata-Ranchi':[0.4,50],'Kolkata-Vizag':[0.7,85],
  'Hyderabad-Pune':[0.65,75],'Hyderabad-Kochi':[0.7,85],'Hyderabad-Goa':[0.7,70],
  'Hyderabad-Vizag':[0.5,60],'Hyderabad-Nagpur':[0.5,65],
  'Kochi-Trivandrum':[0.35,35],'Kochi-Coimbatore':[0.35,40],
  'Goa-Pune':[0.45,50],'Jaipur-Udaipur':[0.4,50],'Jaipur-Jodhpur':[0.35,45],
  'Lucknow-Patna':[0.45,55],'Lucknow-Varanasi':[0.35,40],
};

function getRouteInfo(a,b){return ROUTE_INFO[a+'-'+b]||ROUTE_INFO[b+'-'+a]||[0.9,120];}

// Generate all flights with arrival times
function generateFlights() {
  const flights = [];
  let counter = 100;
  const SLOTS = ['05:00','06:00','07:00','07:45','08:30','09:15','10:00','10:45',
    '11:30','12:15','13:00','13:45','14:30','15:15','16:00','16:45',
    '17:30','18:15','19:00','20:00','21:00','22:00','23:00'];

  for (let i = 0; i < CITIES.length; i++) {
    for (let j = 0; j < CITIES.length; j++) {
      if (i === j) continue;
      const origin = CITIES[i], dest = CITIES[j];
      const [mult, dur] = getRouteInfo(origin, dest);
      const t1 = getTier(origin), t2 = getTier(dest);

      // Tier-based coverage
      const numAl = (t1<=1&&t2<=1)?6 : (t1<=2&&t2<=2)?4 : 2;
      const step = (t1<=1&&t2<=1)?2 : (t1<=2&&t2<=2)?4 : 6;

      for (let a = 0; a < numAl; a++) {
        const al = AIRLINES[a % AIRLINES.length];
        for (let s = a % 3; s < SLOTS.length; s += step) {
          const price = Math.round(al.base * mult + Math.sin(counter)*250 + (s%4)*150);
          const [dh,dm] = SLOTS[s].split(':').map(Number);
          const arrMin = dh*60+dm+dur;
          const arrival = String(Math.floor(arrMin/60)%24).padStart(2,'0')+':'+String(arrMin%60).padStart(2,'0');
          flights.push({
            flight_number: al.code+'-'+counter, origin, destination: dest,
            departure_time: SLOTS[s], arrival_time: arrival, duration: dur,
            airline: al.name, price: Math.max(2500, Math.min(12000, price))
          });
          counter++;
        }
      }
    }
  }
  return flights;
}

const FLIGHTS = generateFlights();

// ===== CONNECTING FLIGHT SEARCH =====
function findConnectingFlights(origin, dest, preferredTime) {
  const connections = [];
  const HUBS = ['Delhi','Mumbai','Bangalore','Chennai','Kolkata','Hyderabad'];
  for (const hub of HUBS) {
    if (hub === origin || hub === dest) continue;
    const leg1s = FLIGHTS.filter(f => f.origin === origin && f.destination === hub);
    const leg2s = FLIGHTS.filter(f => f.origin === hub && f.destination === dest);
    for (const f1 of leg1s) {
      const [ah,am] = f1.arrival_time.split(':').map(Number);
      const arrM = ah*60+am;
      for (const f2 of leg2s) {
        const [dh,dm] = f2.departure_time.split(':').map(Number);
        let layover = dh*60+dm - arrM;
        if (layover < 0) layover += 1440;
        if (layover >= 120 && layover <= 360) {
          connections.push({
            type:'connecting', hub, layover,
            leg1:f1, leg2:f2,
            totalPrice: f1.price+f2.price,
            totalDuration: f1.duration+layover+f2.duration,
            departure_time: f1.departure_time, arrival_time: f2.arrival_time
          });
        }
      }
    }
  }
  connections.sort((a,b) => a.totalDuration-b.totalDuration || a.totalPrice-b.totalPrice);
  return connections.slice(0,10);
}

// ===== AUTOMATED REALISTIC BOOKING =====
function automatedRealisticBooking(origin, destination) {
  const direct = FLIGHTS.filter(f => f.origin===origin && f.destination===destination);
  direct.sort((a,b) => a.price-b.price);
  if (direct.length > 0) {
    const b = direct[0];
    return { type:'direct', itinerary:`${origin}(${IATA_MAP[origin]})→${destination}(${IATA_MAP[destination]})`,
      flights:[b], totalPrice:b.price, totalDuration:b.duration };
  }
  const conn = findConnectingFlights(origin, destination, '10:00');
  if (conn.length > 0) {
    const c = conn[0];
    return { type:'connecting', itinerary:`${origin}→${c.hub}→${destination}`,
      flights:[c.leg1,c.leg2], hub:c.hub, layover:c.layover,
      totalPrice:c.totalPrice, totalDuration:c.totalDuration };
  }
  return { type:'none' };
}

// ===== APP STATE =====
const D = { passengers:[], flights:[], seats:[], bookings:[], nextBid:1 };

// ===== THEME TOGGLE =====
function toggleTheme() {
  document.body.classList.toggle('dark');
  const thumb = document.getElementById('toggleThumb');
  thumb.textContent = document.body.classList.contains('dark') ? '🌙' : '☀️';
}

// ===== NAVIGATION =====
function show(name) {
  document.querySelectorAll('.section').forEach(s => s.classList.remove('active'));
  document.getElementById('sec-' + name).classList.add('active');
  document.querySelectorAll('.nav-a').forEach(a => a.classList.remove('active'));
  document.getElementById('nav-' + name).classList.add('active');
  if (name === 'manage') renderAll();
  if (name === 'bookings') renderBookings();
}
function showManage(name) {
  document.querySelectorAll('.man').forEach(m => m.classList.remove('active'));
  document.getElementById('man-' + name).classList.add('active');
  document.querySelectorAll('.mtab').forEach((b, i) => b.classList.toggle('active', ['passenger','flight','seat'][i] === name));
}

// ===== TOAST =====
function toast(msg, err) {
  const t = document.getElementById('toast');
  t.textContent = msg; t.className = 'toast' + (err ? ' err' : '') + ' show';
  setTimeout(() => t.classList.remove('show'), 2500);
}

// ===== TIME UTILS =====
function timeToMinutes(t) {
  const [h, m] = t.split(':').map(Number);
  return h * 60 + m;
}
function timeDiffMinutes(flightTime, preferredTime) {
  const ft = timeToMinutes(flightTime);
  const pt = timeToMinutes(preferredTime);
  let diff = Math.abs(ft - pt);
  if (diff > 720) diff = 1440 - diff;
  return diff;
}
function formatTime(t) {
  const [h, m] = t.split(':').map(Number);
  const ampm = h >= 12 ? 'PM' : 'AM';
  const h12 = h % 12 || 12;
  return h12 + ':' + String(m).padStart(2, '0') + ' ' + ampm;
}
function formatDiff(mins) {
  if (mins === 0) return '⏱ Exact match';
  const h = Math.floor(mins / 60), m = mins % 60;
  const parts = [];
  if (h) parts.push(h + 'hr');
  if (m) parts.push(m + 'min');
  return '⏱ ' + parts.join(' ') + ' from requested';
}

// ===== ENHANCED FLIGHT SEARCH (State-Based) =====
// Step 1: Check date → Step 2: 4+ results with diversity → Step 3: Present
function searchFlights() {
  const origin = document.getElementById('s-origin').value;
  const dest = document.getElementById('s-dest').value;
  const dateVal = document.getElementById('s-date').value;
  const time = document.getElementById('s-time').value;
  const airline = document.getElementById('s-airline').value;
  const el = document.getElementById('results');
  const datePrompt = document.getElementById('date-prompt');

  if (!origin || !dest) { toast('Please select Origin and Destination', true); return; }
  if (origin === dest) { toast('Origin and Destination must differ', true); return; }

  // ===== STEP 1: Date Gate & Validation =====
  if (dateVal) {
    const selectedDate = new Date(dateVal + 'T00:00:00');
    const today = new Date();
    today.setHours(0,0,0,0);
    
    if (selectedDate < today) {
      toast('Error: Travel date cannot be in the past!', true);
      el.innerHTML = `<div class="search-status search-warn" style="background:rgba(239,68,68,0.1); color:#ef4444; border-color:rgba(239,68,68,0.2)">
        ❌ <b>Invalid Date:</b> You've selected a date in the past (${dateVal}). Please pick a future date to continue.
      </div>`;
      return;
    }
  }

  if (!dateVal) {
    el.innerHTML = '';
    const today = new Date();
    const fmt = d => d.toLocaleDateString('en-IN',{weekday:'short',month:'short',day:'numeric'});
    const iso = d => d.toISOString().split('T')[0];
    const tomorrow = new Date(today); tomorrow.setDate(today.getDate()+1);
    const dayAfter = new Date(today); dayAfter.setDate(today.getDate()+2);
    // Find next Saturday
    const nextSat = new Date(today); nextSat.setDate(today.getDate()+(6-today.getDay()||7));

    datePrompt.style.display = 'block';
    datePrompt.innerHTML = `
      <div class="date-gate-card">
        <div class="dg-icon">📅</div>
        <h3>I've found the route <b>${origin} → ${dest}</b></h3>
        <p>I need to know which date you'd like to fly. Pick a quick option or enter a specific date:</p>
        <div class="dg-options">
          <button class="dg-btn" onclick="selectDate('${iso(today)}')">
            <span class="dg-label">Today</span><span class="dg-date">${fmt(today)}</span>
          </button>
          <button class="dg-btn" onclick="selectDate('${iso(tomorrow)}')">
            <span class="dg-label">Tomorrow</span><span class="dg-date">${fmt(tomorrow)}</span>
          </button>
          <button class="dg-btn" onclick="selectDate('${iso(dayAfter)}')">
            <span class="dg-label">Day After</span><span class="dg-date">${fmt(dayAfter)}</span>
          </button>
          <button class="dg-btn dg-weekend" onclick="selectDate('${iso(nextSat)}')">
            <span class="dg-label">This Weekend</span><span class="dg-date">${fmt(nextSat)}</span>
          </button>
        </div>
      </div>`;
    return;
  }

  datePrompt.style.display = 'none';

  // ===== STEP 2: Search with 4+ result guarantee =====
  // Get all route matches (ignore airline filter for diversity pool)
  let allRouteFlights = FLIGHTS.filter(f => f.origin === origin && f.destination === dest);

  if (allRouteFlights.length === 0) {
    el.innerHTML = `<div class="no-results">
      <h3>😔 No flights on this route</h3>
      <p>No flights available for <b>${origin} → ${dest}</b></p>
      <p style="margin-top:8px;font-size:.85rem">Try a different route.</p>
    </div>`;
    return;
  }

  // Attach time diff
  allRouteFlights = allRouteFlights.map(f => ({
    ...f,
    diffMins: time ? timeDiffMinutes(f.departure_time, time) : 0
  }));

  // Sort by time proximity first, then price
  allRouteFlights.sort((a, b) => a.diffMins - b.diffMins || a.price - b.price);

  // Apply airline filter if set, but keep the full pool for fallback
  let filtered = airline ? allRouteFlights.filter(f => f.airline === airline) : allRouteFlights;

  // Tiered search
  let searchTier = '';
  let tierResults = [];

  if (time) {
    // Tier 1: Exact (±15 min)
    tierResults = filtered.filter(f => f.diffMins <= 15);
    if (tierResults.length > 0) searchTier = 'exact';

    // Tier 2: ±3 hour window
    if (!tierResults.length) {
      tierResults = filtered.filter(f => f.diffMins <= 180);
      if (tierResults.length > 0) searchTier = 'window';
    }

    // Tier 3: Same day — all
    if (!tierResults.length) {
      tierResults = filtered;
      searchTier = 'sameday';
    }
  } else {
    tierResults = filtered;
    searchTier = 'all';
  }

  // ===== ENFORCE 4+ RESULTS with AIRLINE DIVERSITY =====
  // If less than 4, pull from allRouteFlights (ignoring airline filter)
  if (tierResults.length < 4 && !airline) {
    // Already have all, just ensure we show at least 4
    tierResults = allRouteFlights.slice(0, Math.max(4, tierResults.length));
    if (searchTier === 'exact' || searchTier === 'window') searchTier = 'expanded';
  } else if (tierResults.length < 4 && airline) {
    // Relax airline filter to get more results
    const existing = new Set(tierResults.map(f => f.flight_number));
    const extras = allRouteFlights.filter(f => !existing.has(f.flight_number));
    tierResults = [...tierResults, ...extras].slice(0, Math.max(4, tierResults.length));
    if (tierResults.length > filtered.length) searchTier = 'expanded';
  }

  // Airline diversity: ensure at least 2 different carriers if possible
  const uniqueAirlines = [...new Set(tierResults.map(f => f.airline))];
  if (uniqueAirlines.length < 2 && !airline) {
    const firstAirline = uniqueAirlines[0];
    const otherCarriers = allRouteFlights.filter(f => f.airline !== firstAirline);
    if (otherCarriers.length > 0) {
      // Add up to 2 from other carriers
      const existing = new Set(tierResults.map(f => f.flight_number));
      const toAdd = otherCarriers.filter(f => !existing.has(f.flight_number)).slice(0, 2);
      tierResults = [...tierResults, ...toAdd];
      tierResults.sort((a, b) => a.diffMins - b.diffMins || a.price - b.price);
    }
  }

  // ===== STEP 3: Presentation =====
  const dateObj = new Date(dateVal + 'T00:00:00');
  const dateStr = dateObj.toLocaleDateString('en-IN',{weekday:'long',month:'long',day:'numeric',year:'numeric'});
  const oIata = IATA_MAP[origin] || '', dIata = IATA_MAP[dest] || '';

  let header = '';
  if (searchTier === 'exact') {
    header = `<div class="search-status search-success">✅ ${tierResults.length} exact match${tierResults.length>1?'es':''} for ${formatTime(time)} on ${dateStr}</div>`;
  } else if (searchTier === 'window') {
    header = `<div class="search-status search-info">ℹ️ No exact match for ${formatTime(time)}, showing ${tierResults.length} flights within ±3 hours on ${dateStr}</div>`;
  } else if (searchTier === 'sameday' || searchTier === 'expanded') {
    header = `<div class="search-status search-warn">⚠️ I couldn't find a flight for ${formatTime(time)}, but here are the closest ${tierResults.length} options for ${dateStr}</div>`;
  } else {
    header = `<div class="search-status search-success">${tierResults.length} flights available on ${dateStr}</div>`;
  }

  // Airline diversity note
  const shownAirlines = [...new Set(tierResults.map(f => f.airline))];
  if (shownAirlines.length >= 2) {
    header += `<div class="diversity-note">✈️ Showing ${shownAirlines.length} airlines: ${shownAirlines.join(', ')}</div>`;
  }

  // Format duration
  function fmtDur(m) { return Math.floor(m/60)+'h '+((m%60)||'00')+'m'; }

  // Direct flight cards
  let directHTML = tierResults.map(f => `
    <div class="result-card">
      <div>
        <div class="rc-airline">${f.airline}</div>
        <div class="rc-flight">${f.flight_number}</div>
        ${time ? `<div class="rc-diff ${f.diffMins<=15?'diff-exact':f.diffMins<=180?'diff-near':'diff-far'}">${formatDiff(f.diffMins)}</div>` : ''}
      </div>
      <div class="rc-route">
        <div><div class="rc-city">${f.origin} <span class="iata">${oIata}</span></div><div class="rc-time">${formatTime(f.departure_time)}</div></div>
        <div class="rc-line"><span class="rc-dur">Direct • ${fmtDur(f.duration||120)}</span></div>
        <div><div class="rc-city">${f.destination} <span class="iata">${dIata}</span></div><div class="rc-time">${formatTime(f.arrival_time||f.departure_time)}</div></div>
      </div>
      <div class="rc-price">₹${f.price.toLocaleString()}<span>per person</span></div>
      <button class="rc-book" onclick="quickBook('${f.flight_number}')">Book Now</button>
    </div>`).join('');

  // Also find connecting flights for this route
  const connections = findConnectingFlights(origin, dest, time || '12:00');
  let connectHTML = '';
  if (connections.length > 0) {
    connectHTML = `<div class="connect-section">
      <h3 class="connect-header">🔄 Connecting Flights (1-Stop)</h3>` +
      connections.slice(0, 5).map(c => {
        const lH = Math.floor(c.layover/60), lM = c.layover%60;
        const hubIata = IATA_MAP[c.hub] || '';
        return `<div class="result-card connect-card">
          <div class="connect-legs">
            <div class="leg">
              <span class="leg-label">Leg 1</span>
              <div class="rc-airline">${c.leg1.airline} <span class="rc-flight">${c.leg1.flight_number}</span></div>
              <div class="leg-route">${origin} <span class="iata">${oIata}</span> ${formatTime(c.leg1.departure_time)} → ${c.hub} <span class="iata">${hubIata}</span> ${formatTime(c.leg1.arrival_time)}</div>
            </div>
            <div class="layover-badge">⏳ ${lH}h ${lM}m layover at ${c.hub}</div>
            <div class="leg">
              <span class="leg-label">Leg 2</span>
              <div class="rc-airline">${c.leg2.airline} <span class="rc-flight">${c.leg2.flight_number}</span></div>
              <div class="leg-route">${c.hub} <span class="iata">${hubIata}</span> ${formatTime(c.leg2.departure_time)} → ${dest} <span class="iata">${dIata}</span> ${formatTime(c.leg2.arrival_time)}</div>
            </div>
          </div>
          <div>
            <div class="rc-price">₹${c.totalPrice.toLocaleString()}<span>total</span></div>
            <div class="connect-dur">${fmtDur(c.totalDuration)} total</div>
            <button class="rc-book" onclick="quickBookConnect('${c.leg1.flight_number}','${c.leg2.flight_number}')">Book Both</button>
          </div>
        </div>`;
      }).join('') + '</div>';
  }

  el.innerHTML = header + directHTML + connectHTML +
    `<div class="more-options">
      <p>Would you like to see more options or a different date?</p>
      <button class="btn-p" onclick="document.getElementById('s-date').value='';searchFlights()">🗓 Change Date</button>
      <button class="btn-p" style="background:var(--accent)" onclick="document.getElementById('s-time').value='';searchFlights()">🕐 Any Time</button>
      <button class="btn-p" style="background:#16a34a" onclick="document.getElementById('s-airline').value='';searchFlights()">🛫 All Airlines</button>
    </div>`;
}

function quickBook(flightNo) {
  // Find the flight from mock data
  const flight = FLIGHTS.find(f => f.flight_number === flightNo);
  if (!flight) { toast('Flight not found', true); return; }

  // Auto-add the flight to Manage → Flights (if not already there)
  const alreadyAdded = D.flights.find(f => f.id === flightNo);
  if (!alreadyAdded) {
    const newId = flightNo;
    D.flights.push({
      id: newId,
      airline: flight.airline,
      origin: flight.origin,
      destination: flight.destination,
      departure: flight.departure_time,
      seats: 180
    });
    toast('✅ ' + flight.airline + ' ' + flightNo + ' added to Flights & ready to book!');
  } else {
    toast('ℹ️ Flight ' + flightNo + ' already in your list. Proceeding to booking.');
  }

  // Navigate to bookings and pre-fill
  show('bookings');
  document.getElementById('bfno').value = flightNo;
  renderFlights();
}

function selectDate(dateStr) {
  document.getElementById('s-date').value = dateStr;
  document.getElementById('date-prompt').style.display = 'none';
  searchFlights();
}

function quickBookConnect(leg1No, leg2No) {
  // Book both legs as separate flights
  [leg1No, leg2No].forEach(fno => {
    const flight = FLIGHTS.find(f => f.flight_number === fno);
    if (!flight) return;
    const alreadyAdded = D.flights.find(f => f.id === fno);
    if (!alreadyAdded) {
      D.flights.push({
        id: fno, airline: flight.airline,
        origin: flight.origin, destination: flight.destination,
        departure: flight.departure_time, seats: 180
      });
    }
  });
  toast('✅ Both legs added! Enter Passenger ID to book each leg.');
  show('bookings');
  document.getElementById('bfno').value = leg1No;
  renderFlights();
}

// ===== CRUD: PASSENGERS =====
function addPassenger() {
  const id=document.getElementById('pid').value, name=document.getElementById('pname').value,
        phone=document.getElementById('pphone').value, pp=document.getElementById('ppass').value;
  if (!id || !name) { toast('Fill ID and Name', true); return; }
  D.passengers.push({id, name, phone, passport:pp});
  toast('✅ Passenger added!');
  ['pid','pname','pphone','ppass'].forEach(x => document.getElementById(x).value = '');
  renderPassengers();
}
function renderPassengers() {
  const el = document.getElementById('ptable');
  if (!D.passengers.length) { el.innerHTML = '<div class="empty">No passengers yet.</div>'; return; }
  el.innerHTML = '<table><tr><th>ID</th><th>Name</th><th>Phone</th><th>Passport</th></tr>' +
    D.passengers.map(p => `<tr><td>${p.id}</td><td>${p.name}</td><td>${p.phone}</td><td>${p.passport}</td></tr>`).join('') + '</table>';
}

// ===== CRUD: FLIGHTS =====
function addFlight() {
  const id=document.getElementById('fid').value, al=document.getElementById('fairline').value,
        o=document.getElementById('forigin').value, d=document.getElementById('fdest').value,
        t=document.getElementById('ftime').value, s=document.getElementById('fseats').value;
  if (!id || !al) { toast('Fill ID and Airline', true); return; }
  D.flights.push({id, airline:al, origin:o, destination:d, departure:t, seats:parseInt(s)||0});
  toast('✅ Flight added!');
  ['fid','fairline','forigin','fdest','ftime','fseats'].forEach(x => document.getElementById(x).value = '');
  renderFlights();
}
function renderFlights() {
  const el = document.getElementById('ftable');
  if (!D.flights.length) { el.innerHTML = '<div class="empty">No flights yet.</div>'; return; }
  el.innerHTML = '<table><tr><th>ID</th><th>Airline</th><th>Route</th><th>Departure</th><th>Seats</th></tr>' +
    D.flights.map(f => `<tr><td>${f.id}</td><td>${f.airline}</td><td>${f.origin} → ${f.destination}</td><td>${f.departure}</td><td>${f.seats}</td></tr>`).join('') + '</table>';
}

// ===== BOOKING (Auto Seat Assignment) =====
function bookFlight() {
  const pid = document.getElementById('bpid').value;
  const fno = document.getElementById('bfno').value;

  if (!pid || !fno) { toast('Please fill Passenger ID and Flight No', true); return; }
  if (!D.passengers.find(p => p.id == pid)) { toast('Passenger not found! Add them under Manage first.', true); return; }

  // Find the flight
  const flight = D.flights.find(f => f.id === fno || f.id == fno);
  if (!flight) { toast('Flight not found! Search and click "Book Now" first.', true); return; }

  // Check how many seats are already booked on this flight
  const bookedOnFlight = D.bookings.filter(b => b.fno === fno && b.status === 'Confirmed').length;
  const totalSeats = flight.seats || 180;

  if (bookedOnFlight >= totalSeats) {
    toast('Sorry, flight ' + fno + ' is fully booked! (' + totalSeats + '/' + totalSeats + ' seats taken)', true);
    return;
  }

  // Auto-assign the next available seat
  const takenSeats = new Set(D.bookings.filter(b => b.fno === fno && b.status === 'Confirmed').map(b => b.seatNo));
  let assignedSeat = 0;
  for (let s = 1; s <= totalSeats; s++) {
    if (!takenSeats.has(s)) { assignedSeat = s; break; }
  }

  // Determine seat class based on seat number
  let seatClass = 'Economy';
  if (assignedSeat <= 12) seatClass = 'Business';
  else if (assignedSeat <= 36) seatClass = 'Premium Economy';

  D.bookings.push({
    id: D.nextBid++,
    pid,
    fno,
    seatNo: assignedSeat,
    seatClass,
    status: 'Confirmed'
  });

  const remaining = totalSeats - bookedOnFlight - 1;
  toast(`✅ Booking confirmed! Seat ${assignedSeat} (${seatClass}) assigned. ${remaining} seats remaining.`);
  ['bpid','bfno'].forEach(x => document.getElementById(x).value = '');
  renderBookings();
}

function cancelBooking(id) {
  const b = D.bookings.find(x => x.id == id);
  if (!b || b.status === 'Cancelled') return;
  b.status = 'Cancelled';
  toast('Booking #' + id + ' cancelled — Seat ' + b.seatNo + ' released');
  renderBookings();
}

function renderBookings() {
  const el = document.getElementById('btable');
  if (!D.bookings.length) { el.innerHTML = '<div class="empty">No bookings yet.</div>'; return; }
  el.innerHTML = '<table><tr><th>ID</th><th>Passenger</th><th>Flight</th><th>Seat</th><th>Class</th><th>Status</th><th>Action</th></tr>' +
    D.bookings.map(b => {
      const pax = D.passengers.find(p => p.id == b.pid);
      const paxName = pax ? pax.name : b.pid;
      return `<tr><td>#${b.id}</td><td>${paxName}</td><td>${b.fno}</td><td>${b.seatNo}</td><td>${b.seatClass}</td>
      <td><span class="badge ${b.status==='Confirmed'?'badge-b':'badge-r'}">${b.status}</span></td>
      <td>${b.status==='Confirmed'?`<button class="btn-d" onclick="cancelBooking(${b.id})">Cancel</button>`:'-'}</td></tr>`;
    }).join('') + '</table>';
}

function renderAll() { renderPassengers(); renderFlights(); }

// ===== INITIALIZATION =====
window.onload = () => {
  const dateInput = document.getElementById('s-date');
  if (dateInput) {
    dateInput.min = new Date().toISOString().split('T')[0];
  }
  renderAll();
};
